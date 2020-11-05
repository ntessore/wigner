// wigner_3j_m
// ===========
//
// Evaluate the 3j symbol g(m2) = (l1 l2   l3  )
//                                (m1 m2 -m1-m2)
// for all allowed values of m2, the other parameters being held fixed.
//
// Origin
// ------
// SLATEC, http://www.netlib.org/slatec.
//
// Keywords
// --------
// 3j coefficients, 3j symbols, Clebsch-Gordan coefficients,
// Racah coefficients, vector addition coefficients, Wigner coefficients
//
// Author
// ------
// Gordon, R. G., Harvard University
// Schulten, K., Max Planck Institute
//
// Usage
// -----
// int wigner_3j_m(double l1, double l2, double l3, double m1, double* m2min,
//                 double* m2max, double* thrcof, int ndim);
//
// Arguments
// ---------
// l1 : double
//     Parameter in 3j symbol.
// l2 : double
//     Parameter in 3j symbol.
// l3 : double
//     Parameter in 3j symbol.
// m1 : double
//     Parameter in 3j symbol.
// m2min : double*, out
//     Smallest allowable m2 in 3j symbol.
// m2max : double*, out
//     Largest allowable m2 in 3j symbol.
// thrcof : double* out
//     Set of 3j coefficients generated by evaluating the 3j symbol for all
//     allowed values of m2.  The size of `thrcof` must be `m2max-m2min+1`
//     and `thrcof[i]` will contain g(m2min+i), i=0, 1, ..., m2max-m2min.
//     If `thrcof` is `NULL`, the function will return after `m2min` and
//     `m2max` are set, so that an array of the correct size can be allocated
//     for a subsequent function call.
// ndim : int
//     Declared length of `thrcof` in calling program. If `thrcof` is `NULL`,
//     then `ndim` should be set to 0.
//
// Returns
// -------
// ier : int
//     Error flag.
//     ier=0 No errors.
//     ier=1 Either `l1 < abs(m1)` or `l1+abs(m1)` non-integer.
//     ier=2 `abs(l1-l2) <= l3 <= l1+l2` not satisfied.
//     ier=3 `l1+l2+l3` not an integer.
//     ier=4 `m2max-m2min` not an integer.
//     ier=5 `m2max` less than `m2min`.
//     ier=6 `ndim` less than `m2max-m2min+1`.
//
// Description
// -----------
// Although conventionally the parameters of the vector addition
// coefficients satisfy certain restrictions, such as being integers
// or integers plus 1/2, the restrictions imposed on input to this
// subroutine are somewhat weaker. See, for example, Section 27.9 of
// Abramowitz and Stegun or Appendix C of Volume II of A. Messiah.
// The restrictions imposed by this subroutine are
//      1. `l1 >= abs(m1)` and `l1+abs(m1)` must be an integer;
//      2. `abs(l1-l2)` <= l3 <= l1+l2`;
//      3. `l1+l2+l3` must be an integer;
//      4. `m2max-m2min` must be an integer, where
//         `m2max=min(l2,l3-m1)` and `m2min=max(-l2,-l3-m1)`.
// If the conventional restrictions are satisfied, then these
// restrictions are met.
//
// The user should be cautious in using input parameters that do
// not satisfy the conventional restrictions. For example, the
// the subroutine produces values of
//      g(M2) = (0.75 1.50   1.75  )
//              (0.25  m2  -0.25-m2)
// for m2=-1.5,-0.5,0.5,1.5 but none of the symmetry properties of the
// 3j symbol, set forth on page 1056 of Messiah, is satisfied.
//
// The subroutine generates g(m2min), g(m2min+1), ..., g(m2max)
// where `m2min` and `m2max` are defined above. The sequence g(m2) is
// generated by a three-term recurrence algorithm with scaling to
// control overflow. Both backward and forward recurrence are used to
// maintain numerical stability. The two recurrence sequences are
// matched at an interior point and are normalized from the unitary
// property of 3j coefficients and Wigner's phase convention.
//
// The algorithm is suited to applications in which large quantum
// numbers arise, such as in molecular dynamics.
//
// References
// ----------
// 1. Abramowitz, M., and Stegun, I. A., Eds., Handbook of Mathematical
//    Functions with Formulas, Graphs and Mathematical Tables, NBS Applied
//    Mathematics Series 55, June 1964 and subsequent printings.
// 2. Messiah, Albert., Quantum Mechanics, Volume II, North-Holland
//    Publishing Company, 1963.
// 3. Schulten, Klaus and Gordon, Roy G., Exact recursive evaluation of 3j
//    and 6j coefficients for quantum-mechanical coupling of angular momenta,
//    J Math Phys, v 16, no. 10, October 1975, pp. 1961-1970.
// 4. Schulten, Klaus and Gordon, Roy G., Semiclassical approximations to 3j
//    and 6j coefficients for quantum-mechanical coupling of angular momenta,
//    J Math Phys, v 16, no. 10, October 1975, pp. 1971-1988.
// 5. Schulten, Klaus and Gordon, Roy G., Recursive evaluation of 3j and 6j
//    coefficients, Computer Phys Comm, v 11, 1976, pp. 269-278.
//
// Revision history
// ----------------
// 01 Jan 1975  DATE WRITTEN
// 15 May 1988  SLATEC prologue added by G. C. Nielson, NBS; parameters
//              HUGE and TINY revised to depend on D1MACH.
// 29 Dec 1989  Prologue description rewritten; other prologue sections
//              revised; MMATCH (location of match point for recurrences)
//              removed from argument list; argument IER changed to serve
//              only as an error flag (previously, in cases without error,
//              it returned the number of scalings); number of error codes
//              increased to provide more precise error information;
//              program comments revised; SLATEC error handler calls
//              introduced to enable printing of error messages to meet
//              SLATEC standards. These changes were done by D. W. Lozier,
//              M. A. McClain and J. M. Smith of the National Institute
//              of Standards and Technology, formerly NBS.
// 15 Apr 1991  Mixed type expressions eliminated; variable C1 initialized;
//              description of THRCOF expanded. These changes were done by
//              D. W. Lozier.
// 04 Nov 2020  Translation to C by N. Tessore.
//

#include <math.h>
#include <float.h>

static inline int phase(int m)
{
    return 1-2*(m&1);
}

int wigner_3j_m(double l1, double l2, double l3, double m1, double* m2min_out,
                double* m2max_out, double* thrcof, int ndim)
{
    // variables
    int i, index, lstep, n, nfin, nfinp1, nfinp2, nlim, nstep2;
    double a1, a1s, c1, c1old, c2, cnorm, dv, m2, m2min, m2max, m3, newfac,
           oldfac, ratio, sign1, sign2, sum1, sum2, sumbac, sumfor, sumuni,
           thresh, x, x1, x2, x3, y, y1, y2, y3;

    // constants
    const double eps = .01;

    // HUGE is the square root of one twentieth of the largest floating
    // point number, approximately.
    const double huge = sqrt(DBL_MAX/20);
    const double srhuge = sqrt(huge);
    const double tiny = 1.0/huge;
    const double srtiny = 1.0/srhuge;

    // Check error condition 1.
    if((l1-fabs(m1)+eps < 0) || (fmod(l1+fabs(m1)+eps, 1) >= eps+eps))
        return 1;

    // Check error condition 2.
    if((l1+l2-l3 < -eps) || (l1-l2+l3 < -eps) || (-l1+l2+l3 < -eps))
       return 2;

    // Check error condition 3.
    if(fmod(l1+l2+l3+eps, 1) >= eps+eps)
        return 3;

    // Limits for m2
    *m2min_out = m2min = fmax(-l2, -l3-m1);
    *m2max_out = m2max = fmin(l2, l3-m1);

    // Check error condition 4.
    if(fmod(m2max-m2min+eps, 1) >= eps+eps)
       return 4;

    // Check error condition 5.
    if(m2min >= m2max+eps)
        return 5;

    // Only report m2min and m2max.
    if(!thrcof)
        return 0;

    // Number of coefficients to compute.
    nfin = m2max-m2min+1+eps;

    // Check error condition 6.
    if(ndim < nfin)
        return 6;

    // Check whether m2 can take only one value, ie. m2min = m2max.
    if(m2min >= m2max-eps)
    {
        thrcof[0] = phase(fabs(l2-l3-m1)+eps)/sqrt(l1+l2+l3+1);
        return 0;
    }

    // This is reached in case that m2 and m3 take more than one value,
    // i.e. m2min < m2max.

    // Start of forward recursion from m2 = m2min
    m2 = m2min;
    thrcof[0] = srtiny;
    newfac = 0.;
    c1 = 0.;
    sum1 = tiny;

    for(lstep = 2;; lstep += 1)
    {
        m2 = m2 + 1;
        m3 = - m1 - m2;

        c1old = fabs(c1);
        oldfac = newfac;
        a1 = (l2-m2+1) * (l2+m2) * (l3+m3+1) * (l3-m3);
        newfac = sqrt(a1);

        dv = (l1+l2+l3+1)*(l2+l3-l1) - (l2-m2+1)*(l3+m3+1)
                                     - (l2+m2-1)*(l3-m3-1);

        c1 = - dv / newfac;

        // If m2 = m2min + 1, the third term in the recursion equation vanishes,
        // hence
        if(lstep == 2)
        {
            x = srtiny * c1;
            thrcof[1] = x;
            sum1 = sum1 + tiny * (c1*c1);
            if(lstep == nfin)
                goto nobac;
        }
        else
        {
            c2 = - oldfac / newfac;

            // Recursion to the next 3j coefficient
            x = c1 * thrcof[lstep-2] + c2 * thrcof[lstep-3];
            thrcof[lstep-1] = x;
            sumfor = sum1;
            sum1 = sum1 + x*x;
            if(lstep == nfin)
                break;

            // See if last unnormalized 3j coefficient exceeds srhuge
            if(fabs(x) > srhuge)
            {
                // This is reached if last 3j coefficient larger than srhuge,
                // so that the recursion series thrcof[0], ... , thrcof[lstep-1]
                // has to be rescaled to prevent overflow
                for(i = 0; i < lstep; ++i)
                {
                    if(fabs(thrcof[i]) < srtiny)
                        thrcof[i] = 0;
                    else
                        thrcof[i] = thrcof[i] / srhuge;
                }
                sum1 = sum1 / huge;
                sumfor = sumfor / huge;
                x = x / srhuge;
            }

            // As long as abs(c1) is decreasing, the recursion proceeds towards
            // increasing 3j values and, hence, is numerically stable.  Once
            // an increase of abs(c1) is detected, the recursion direction is
            // reversed.
            if(c1old <= fabs(c1))
                break;
        }
    }

    // Keep three 3j coefficients around mmatch for comparison later
    // with backward recursion values.
    x1 = x;
    x2 = thrcof[lstep-2];
    x3 = thrcof[lstep-3];
    nstep2 = nfin - lstep + 3;

    // Starting backward recursion from m2max taking nstep2 steps, so
    // that forwards and backwards recursion overlap at the three points
    // m2 = mmatch+1, mmatch, mmatch-1.
    nfinp1 = nfin + 1;
    nfinp2 = nfin + 2;
    thrcof[nfin-1] = srtiny;
    sum2 = tiny;

    m2 = m2max + 2;
    for(lstep = 2;; lstep += 1)
    {
        m2 = m2 - 1;
        m3 = - m1 - m2;

        oldfac = newfac;
        a1s = (l2-m2+2) * (l2+m2-1) * (l3+m3+2) * (l3-m3-1);
        newfac = sqrt(a1s);
        dv = (l1+l2+l3+1)*(l2+l3-l1) - (l2-m2+1)*(l3+m3+1)
                                     - (l2+m2-1)*(l3-m3-1);

        c1 = - dv / newfac;

        // If m2 = m2max + 1 the third term in the recursion equation vanishes
        if(lstep == 2)
        {
            y = srtiny * c1;
            thrcof[nfin-2] = y;

            if(lstep == nstep2)
                break;

            sumbac = sum2;
            sum2 = sum2 + y*y;
        }
        else
        {
            c2 = - oldfac / newfac;

            // Recursion to the next 3j coefficient
            y = c1 * thrcof[nfinp1-lstep] + c2 * thrcof[nfinp2-lstep];

            if(lstep == nstep2)
                break;

            thrcof[nfin-lstep] = y;
            sumbac = sum2;
            sum2 = sum2 + y*y;


            // See if last 3j coefficient exceeds srhuge
            if(fabs(y) > srhuge)
            {

                // This is reached if last 3j coefficient larger than SRHUGE,
                // so that the recursion series thrcof[nfin-1], ... ,
                // thrcof[nfin-lstep] has to be rescaled to prevent overflow.
                for(i = 1; i <= lstep; ++i)
                {
                    index = nfin - i;
                    if(fabs(thrcof[index]) < srtiny)
                        thrcof[index] = 0;
                    else
                        thrcof[index] = thrcof[index] / srhuge;
                }
                sum2 = sum2 / huge;
                sumbac = sumbac / huge;
            }
        }
    }

    // The forward recursion 3j coefficients x1, x2, x3 are to be matched
    // with the corresponding backward recursion values y1, y2, y3.
    y3 = y;
    y2 = thrcof[nfinp1-lstep];
    y1 = thrcof[nfinp2-lstep];

    // Determine now ratio such that yi = ratio * xi  (i=1,2,3) holds
    // with minimal error.
    ratio = ( x1*y1 + x2*y2 + x3*y3 ) / ( x1*x1 + x2*x2 + x3*x3 );
    nlim = nfin - nstep2 + 1;

    if(fabs(ratio) >= 1)
    {
        for(n = 0; n < nlim; ++n)
            thrcof[n] = ratio * thrcof[n];
        sumuni = ratio * ratio * sumfor + sumbac;
    }
    else
    {
        ratio = 1 / ratio;
        for(n = nlim; n < nfin; ++n)
            thrcof[n] = ratio * thrcof[n];
        sumuni = sumfor + ratio*ratio*sumbac;
    }

    goto norm;

    nobac:
    sumuni = sum1;

    // Normalize 3j coefficients
    norm:
    cnorm = 1 / sqrt((l1+l1+1) * sumuni);

    // Sign convention for last 3j coefficient determines overall phase
    sign1 = copysign(1, thrcof[nfin-1]);
    sign2 = phase(fabs(l2-l3-m1)+eps);
    if(sign1*sign2 < 0)
        cnorm = - cnorm;

    if(fabs(cnorm) < 1)
    {
        thresh = tiny / fabs(cnorm);
        for(n = 0; n < nfin; ++n)
        {
            if(fabs(thrcof[n]) < thresh)
                thrcof[n] = 0;
            else
                thrcof[n] = cnorm * thrcof[n];
        }
    }
    else
    {
        for(n = 0; n < nfin; ++n)
            thrcof[n] = cnorm * thrcof[n];
    }
    
    return 0;
}
