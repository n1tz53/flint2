/*=============================================================================

    This file is part of FLINT.

    FLINT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    FLINT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FLINT; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA

=============================================================================*/
/******************************************************************************

    Copyright (C) 2015 Nitin Kumar

******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "flint.h"
#include "ulong_extras.h"
#include "fmpz.h"
#include "qsieve.h"

int main(void)
{
   int i, j;
   mp_limb_t small_factor;
   fmpz_t n;
   fmpz_factor_t factors;
   fmpz_init(n);
   FLINT_TEST_INIT(state);

   flint_printf("factor....");
   fflush(stdout);



   for (i = 0; i < 1 * flint_test_multiplier(); i++) /* Test random n */
   {
      fmpz_randtest_unsigned(n, state, 130);

      if (fmpz_is_zero(n) || fmpz_is_one(n)) continue;

      fmpz_factor_init(factors);
      qsieve_factor(n, factors);

      for (j = 0; j < factors->num; j++)
      {
          if (fmpz_fdiv_ui(n, fmpz_get_ui(&factors->p[j])))
          {
              flint_printf("%wd is not a factor of ",
                           fmpz_get_ui(&factors->p[j]));
              fmpz_print(n);
              flint_printf("\n");
              abort();
          }
      }

      fmpz_factor_clear(factors);

   }

   fmpz_clear(n);

   FLINT_TEST_CLEANUP(state);

   flint_printf("PASS\n");
   return 0;
}