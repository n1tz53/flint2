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

    Copyright (C) 2011 Sebastian Pancratz

******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "flint.h"
#include "fmpz.h"
#include "fmpq.h"

int
main(void)
{
    int i, result;
    FLINT_TEST_INIT(state);
    

    flint_printf("mul_fmpz....");
    fflush(stdout);

    /* Aliasing x = x*z */
    for (i = 0; i < 10000; i++)
    {
        fmpq_t x, y;
        fmpz_t z;

        fmpq_init(x);
        fmpq_init(y);
        fmpz_init(z);

        fmpq_randtest(x, state, 200);
        fmpz_randtest(z, state, 200);

        fmpq_mul_fmpz(y, x, z);
        fmpq_mul_fmpz(x, x, z);

        result = (fmpq_is_canonical(x) && fmpq_is_canonical(y) && fmpq_equal(x, y));
        if (!result)
        {
            flint_printf("FAIL (alias):\n");
            flint_printf("x = "), fmpq_print(x), flint_printf("\n");
            flint_printf("y = "), fmpq_print(y), flint_printf("\n");
            flint_printf("z = "), fmpz_print(z), flint_printf("\n");
            abort();
        }

        fmpq_clear(x);
        fmpq_clear(y);
        fmpz_clear(z);
    }

    /* Compare with fmpq_mul */
    for (i = 0; i < 10000; i++)
    {
        fmpq_t x, y, z;

        fmpq_init(x);
        fmpq_init(y);
        fmpq_init(z);

        fmpq_randtest(x, state, 200);
        fmpz_randtest(fmpq_numref(z), state, 200);

        fmpq_mul_fmpz(y, x, fmpq_numref(z));
        fmpq_mul(x, x, z);

        result = (fmpq_is_canonical(x) && fmpq_is_canonical(y) && fmpq_equal(x, y));
        if (!result)
        {
            flint_printf("FAIL (cmp):\n");
            flint_printf("x = "), fmpq_print(x), flint_printf("\n");
            flint_printf("y = "), fmpq_print(y), flint_printf("\n");
            flint_printf("z = "), fmpq_print(z), flint_printf("\n");
            abort();
        }

        fmpq_clear(x);
        fmpq_clear(y);
        fmpq_clear(z);
    }

    

    FLINT_TEST_CLEANUP(state);
    flint_printf("PASS\n");
    return EXIT_SUCCESS;
}

