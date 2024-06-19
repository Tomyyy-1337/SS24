#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#ifdef _OPENMP
#include <omp.h>
#endif
#include <assert.h>
// #include <sys/mman.h>

#define REAL float
#ifndef NX
#define NX (64)
#endif

#ifndef M_PI
#define M_PI (3.1415926535897932384626)
#endif


void init(REAL *buff, const int nx, const int ny, const int nz,
          const REAL kx, const REAL ky, const REAL kz,
          const REAL dx, const REAL dy, const REAL dz,
          const REAL kappa, const REAL time) {
  REAL ax, ay, az;
  int jz, jy, jx;
  ax = exp(-kappa*time*(kx*kx));
  ay = exp(-kappa*time*(ky*ky));
  az = exp(-kappa*time*(kz*kz));
  for (jz = 0; jz < nz; jz++) {
    for (jy = 0; jy < ny; jy++) {
      for (jx = 0; jx < nx; jx++) {
        int j = jz*nx*ny + jy*nx + jx;
        REAL x = dx*((REAL)(jx + 0.5));
        REAL y = dy*((REAL)(jy + 0.5));
        REAL z = dz*((REAL)(jz + 0.5));
        REAL f0 = (REAL)0.125
          *(1.0 - ax*cos(kx*x))
          *(1.0 - ay*cos(ky*y))
          *(1.0 - az*cos(kz*z));
        buff[j] = f0;
      }
    }
  }
}

REAL accuracy(const REAL *b1, REAL *b2, const int len) {
  REAL err = 0.0;
  int i;
  for (i = 0; i < len; i++) {
    err += (b1[i] - b2[i]) * (b1[i] - b2[i]);
  }
  return (REAL)sqrt(err/len);
}

void
diffusion_baseline(REAL *f1, REAL *f2, int nx, int ny, int nz,
                   REAL ce, REAL cw, REAL cn, REAL cs, REAL ct,
                   REAL cb, REAL cc, REAL dt,
                   int count) {

    int i, x, y, z;
    int c, w, e, n, s, b, t;
    for (i = 0; i < count; ++i) {

        //z loop first step unrolled
        {
        z = 0;
        //y loop first step unrolled
            {
            y = 0;
            //x loop first step unrolled
            x = 0;
            c =  0;
            e = c + 1;
            s = c + nx;
            t = c + nx * ny;
            f2[c] = cc * f1[c] + cw * f1[c] + ce * f1[e] + cs * f1[s] + cn * f1[c] + cb * f1[c] + ct * f1[t];
            //x loop begins
            for (x = 1; x < nx-1; x++) {
                c =  x;
                w = c - 1;
                e = c + 1;
                s = c + nx;
                t = c + nx * ny;
                f2[c] = cc * f1[c] + cw * f1[w] + ce * f1[e] + cs * f1[s] + cn * f1[c] + cb * f1[c] + ct * f1[t];
            }
            //x loop ends
            //x loop last step unrolled
            c =  x;
            w = c - 1;
            s = c + nx;
            t = c + nx * ny;
            f2[c] = cc * f1[c] + cw * f1[w] + ce * f1[c] + cs * f1[s] + cn * f1[c] + cb * f1[c] + ct * f1[t];

            }
            //y loop begins
            for (y = 1; y < ny-1; y++) {
                //x loop first step unrolled
                x = 0;
                c =  x + y * nx;
                e = c + 1;
                n = c - nx;
                s = c + nx;
                t = c + nx * ny;
                f2[c] = cc * f1[c] + cw * f1[c] + ce * f1[e] + cs * f1[s] + cn * f1[n] + cb * f1[c] + ct * f1[t];
                //x loop begins
                for (x = 1; x < nx-1; x++) {
                    c =  x + y * nx;
                    w = c - 1;
                    e = c + 1;
                    n = c - nx;
                    s = c + nx;
                    t = c + nx * ny;
                    f2[c] = cc * f1[c] + cw * f1[w] + ce * f1[e] + cs * f1[s] + cn * f1[n] + cb * f1[c] + ct * f1[t];
                }
                //x loop ends
                //x loop last step unrolled
                c =  x + y * nx;
                w = c - 1;
                n = c - nx;
                s = c + nx;
                t = c + nx * ny;
                f2[c] = cc * f1[c] + cw * f1[w] + ce * f1[c] + cs * f1[s] + cn * f1[n] + cb * f1[c] + ct * f1[t];
            }
            //y loop ends
            //y loop last step unrolled
            {
            //x loop first step unrolled
            x = 0;
            c =  x + y * nx;
            e = c + 1;
            n = c - nx;
            t = c + nx * ny;
            f2[c] = cc * f1[c] + cw * f1[c] + ce * f1[e] + cs * f1[c] + cn * f1[n] + cb * f1[c] + ct * f1[t];
            //x loop begins
            for (x = 1; x < nx-1; x++) {
                c =  x + y * nx;
                w = c - 1;
                e = c + 1;
                n = c - nx;
                t = c + nx * ny;
                f2[c] = cc * f1[c] + cw * f1[w] + ce * f1[e] + cs * f1[c] + cn * f1[n] + cb * f1[c] + ct * f1[t];
            }
            //x loop ends
            //x loop last step unrolled
            c =  x + y * nx;
            w = c - 1;
            n = c - nx;
            t = c + nx * ny;
            f2[c] = cc * f1[c] + cw * f1[w] + ce * f1[c] + cs * f1[c] + cn * f1[n] + cb * f1[c] + ct * f1[t];
            }
        }
        //z loop begins
        for (z = 1; z < nz-1; z++) {
            //y loop first step unrolled
            {
            y = 0;
            //x loop first step unrolled
            x = 0;
            c =  x + y * nx + z * nx * ny;
            e = c + 1;
            s = c + nx;
            b = c - nx * ny;
            t = c + nx * ny;
            f2[c] = cc * f1[c] + cw * f1[c] + ce * f1[e] + cs * f1[s] + cn * f1[c] + cb * f1[b] + ct * f1[t];
            //x loop begins
            for (x = 1; x < nx-1; x++) {
                c =  x + y * nx + z * nx * ny;
                w = c - 1;
                e = c + 1;
                s = c + nx;
                b = c - nx * ny;
                t = c + nx * ny;
                f2[c] = cc * f1[c] + cw * f1[w] + ce * f1[e] + cs * f1[s] + cn * f1[c] + cb * f1[b] + ct * f1[t];
            }
            //x loop ends
            //x loop last step unrolled
            c =  x + y * nx + z * nx * ny;
            w = c - 1;
            s = c + nx;
            b = c - nx * ny;
            t = c + nx * ny;
            f2[c] = cc * f1[c] + cw * f1[w] + ce * f1[c] + cs * f1[s] + cn * f1[c] + cb * f1[b] + ct * f1[t];

            }
            //y loop begins
            for (y = 1; y < ny-1; y++) {
                //x loop first step unrolled
                x = 0;
                c =  x + y * nx + z * nx * ny;
                e = c + 1;
                n = c - nx;
                s = c + nx;
                b = c - nx * ny;
                t = c + nx * ny;
                f2[c] = cc * f1[c] + cw * f1[c] + ce * f1[e] + cs * f1[s] + cn * f1[n] + cb * f1[b] + ct * f1[t];
                //x loop begins
                for (x = 1; x < nx-1; x++) {
                    c =  x + y * nx + z * nx * ny;
                    w = c - 1;
                    e = c + 1;
                    n = c - nx;
                    s = c + nx;
                    b = c - nx * ny;
                    t = c + nx * ny;
                    f2[c] = cc * f1[c] + cw * f1[w] + ce * f1[e] + cs * f1[s] + cn * f1[n] + cb * f1[b] + ct * f1[t];
                }
                //x loop ends
                //x loop last step unrolled
                c =  x + y * nx + z * nx * ny;
                w = c - 1;
                n = c - nx;
                s = c + nx;
                b = c - nx * ny;
                t = c + nx * ny;
                f2[c] = cc * f1[c] + cw * f1[w] + ce * f1[c] + cs * f1[s] + cn * f1[n] + cb * f1[b] + ct * f1[t];
            }
            //y loop ends
            //y loop last step unrolled
            {
            //x loop first step unrolled
            x = 0;
            c =  y * nx + z * nx * ny;
            e = c + 1;
            n = c - nx;
            b = c - nx * ny;
            t = c + nx * ny;
            f2[c] = cc * f1[c] + cw * f1[c] + ce * f1[e] + cs * f1[c] + cn * f1[n] + cb * f1[b] + ct * f1[t];
            //x loop begins
            for (x = 1; x < nx-1; x++) {
                c =  x + y * nx + z * nx * ny;
                w = c - 1;
                e = c + 1;
                n = c - nx;
                b = c - nx * ny;
                t = c + nx * ny;
                f2[c] = cc * f1[c] + cw * f1[w] + ce * f1[e] + cs * f1[c] + cn * f1[n] + cb * f1[b] + ct * f1[t];
            }
            //x loop ends
            //x loop last step unrolled
            c =  x + y * nx + z * nx * ny;
            w = c - 1;
            n = c - nx;
            b = c - nx * ny;
            t = c + nx * ny;
            f2[c] = cc * f1[c] + cw * f1[w] + ce * f1[c] + cs * f1[c] + cn * f1[n] + cb * f1[b] + ct * f1[t];
            }
        }
        //z loop ends
        //z loop last step unrolled
        {
        //y loop first step unrolled
            {
            y = 0;
            //x loop first step unrolled
            x = 0;
            c =  x + y * nx + z * nx * ny;
            e = c + 1;
            s = c + nx;
            b = c - nx * ny;
            f2[c] = cc * f1[c] + cw * f1[c] + ce * f1[e] + cs * f1[s] + cn * f1[c] + cb * f1[b] + ct * f1[c];
            //x loop begins
            for (x = 1; x < nx-1; x++) {
                c =  x + y * nx + z * nx * ny;
                w = c - 1;
                e = c + 1;
                s = c + nx;
                b = c - nx * ny;
                f2[c] = cc * f1[c] + cw * f1[w] + ce * f1[e] + cs * f1[s] + cn * f1[c] + cb * f1[b] + ct * f1[c];
            }
            //x loop ends
            //x loop last step unrolled
            c =  x + y * nx + z * nx * ny;
            w = c - 1;
            s = c + nx;
            b = c - nx * ny;
            f2[c] = cc * f1[c] + cw * f1[w] + ce * f1[c] + cs * f1[s] + cn * f1[c] + cb * f1[b] + ct * f1[c];

            }
            //y loop begins
            for (y = 1; y < ny-1; y++) {
                //x loop first step unrolled
                x = 0;
                c =  x + y * nx + z * nx * ny;
                e = c + 1;
                n = c - nx;
                s = c + nx;
                b = c - nx * ny;
                f2[c] = cc * f1[c] + cw * f1[c] + ce * f1[e] + cs * f1[s] + cn * f1[n] + cb * f1[b] + ct * f1[c];
                //x loop begins
                for (x = 1; x < nx-1; x++) {
                    c =  x + y * nx + z * nx * ny;
                    w = c - 1;
                    e = c + 1;
                    n = c - nx;
                    s = c + nx;
                    b = c - nx * ny;
                    f2[c] = cc * f1[c] + cw * f1[w] + ce * f1[e] + cs * f1[s] + cn * f1[n] + cb * f1[b] + ct * f1[c];
                }
                //x loop ends
                //x loop last step unrolled
                c =  x + y * nx + z * nx * ny;
                w = c - 1;
                n = c - nx;
                s = c + nx;
                b = c - nx * ny;
                f2[c] = cc * f1[c] + cw * f1[w] + ce * f1[c] + cs * f1[s] + cn * f1[n] + cb * f1[b] + ct * f1[c];
            }
            //y loop ends
            //y loop last step unrolled
            {
            //x loop first step unrolled
            x = 0;
            c =  x + y * nx + z * nx * ny;
            e = c + 1;
            n = c - nx;
            b = c - nx * ny;
            f2[c] = cc * f1[c] + cw * f1[c] + ce * f1[e] + cs * f1[c] + cn * f1[n] + cb * f1[b] + ct * f1[c];
            //x loop begins
            for (x = 1; x < nx-1; x++) {
                c =  x + y * nx + z * nx * ny;
                w = c - 1;
                e = c + 1;
                n = c - nx;
                b = c - nx * ny;
                f2[c] = cc * f1[c] + cw * f1[w] + ce * f1[e] + cs * f1[c] + cn * f1[n] + cb * f1[b] + ct * f1[c];
            }
            //x loop ends
            //x loop last step unrolled
            c =  x + y * nx + z * nx * ny;
            w = c - 1;
            n = c - nx;
            b = c - nx * ny;
            f2[c] = cc * f1[c] + cw * f1[w] + ce * f1[c] + cs * f1[c] + cn * f1[n] + cb * f1[b] + ct * f1[c];
            }
        }
        REAL *t = f1;
        f1 = f2;
        f2 = t;
    }



  return;
}

static double cur_second(void) {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (double)tv.tv_sec + (double)tv.tv_usec / 1000000.0;
}


void dump_result(REAL *f, int nx, int ny, int nz, char *out_path) {
  FILE *out = fopen(out_path, "w");
  assert(out);
  size_t nitems = nx * ny * nz;
  fwrite(f, sizeof(REAL), nitems, out);
  fclose(out);
}

int main(int argc, char *argv[]) 
{
  
  struct timeval time_begin, time_end;

  int    nx    = NX;
  int    ny    = NX;
  int    nz    = NX;

  REAL *f1 = (REAL *)malloc(sizeof(REAL)*NX*NX*NX);
  REAL *f2 = (REAL *)malloc(sizeof(REAL)*NX*NX*NX);
  // assert(f1 != MAP_FAILED);
  // assert(f2 != MAP_FAILED);
  REAL *answer = (REAL *)malloc(sizeof(REAL) * nx*ny*nz);
  REAL *f_final = NULL;

  REAL   time  = 0.0;
  int    count = 0;  
  int    nthreads;

  REAL l, dx, dy, dz, kx, ky, kz, kappa, dt;
  REAL ce, cw, cn, cs, ct, cb, cc;

#ifdef _OPENMP
  #pragma omp parallel
  #pragma omp master
    nthreads = omp_get_num_threads();
#else
    nthreads=1;
#endif

  l = 1.0;
  kappa = 0.1;
  dx = dy = dz = l / nx;
  kx = ky = kz = 2.0 * M_PI;
  dt = 0.1*dx*dx / kappa;
 #ifdef _OPENMP
  count = 0.1 / dt;
 #else
  dy=(4096.*4096.*dt*dx*kx*kx)/kappa/kappa;
  count=(int)dy;
  dy=dx;
 #endif	
  f_final = (count % 2)? f2 : f1;

  init(f1, nx, ny, nz, kx, ky, kz, dx, dy, dz, kappa, time);

  ce = cw = kappa*dt/(dx*dx);
  cn = cs = kappa*dt/(dy*dy);
  ct = cb = kappa*dt/(dz*dz);
  cc = 1.0 - (ce + cw + cn + cs + ct + cb);

  printf("Running diffusion kernel (%d,%d,%d) %d times\n", nx,ny,nz,count); 
  fflush(stdout);
  gettimeofday(&time_begin, NULL);
  diffusion_baseline(f1, f2, nx, ny, nz, ce, cw, cn, cs, ct, cb, cc,
                 dt, count);
  gettimeofday(&time_end, NULL);
  time = count * dt;
  dump_result(f_final, nx, ny, nz, "diffusion_result.dat");

  init(answer, nx, ny, nz, kx, ky, kz, dx, dy, dz, kappa, time);
  REAL err = accuracy(f_final, answer, nx*ny*nz);
  double elapsed_time = (time_end.tv_sec - time_begin.tv_sec)
      + (time_end.tv_usec - time_begin.tv_usec)*1.0e-6;
  REAL mflops = (nx*ny*nz)*13.0*count/elapsed_time * 1.0e-06;
  double thput = (nx * ny * nz) * sizeof(REAL) * 3.0 * count
      / elapsed_time * 1.0e-09;

  fprintf(stderr, "Elapsed time : %.3f (s)\n", elapsed_time);
  fprintf(stderr, "FLOPS        : %.3f (MFlops)\n", mflops);
  fprintf(stderr, "Throughput   : %.3f (GB/s)\n", thput);  
  fprintf(stderr, "Accuracy     : %e\n", err);
  
  free(f1);
  free(f2);
  return 0;
}
