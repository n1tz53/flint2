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

    Copyright (C) 2011 Fredrik Johansson
    Copyright (C) 2014 William Hart

******************************************************************************/

#include "fmpq.h"

void
_fmpq_sub_si(fmpz_t rnum, fmpz_t rden, const fmpz_t p, const fmpz_t q,
            slong r)
{
    fmpz_t u;

    /* both are integers */
    if (fmpz_is_one(q))
    {
        if (r >= 0)
           fmpz_sub_ui(rnum, p, r);
        else
           fmpz_add_ui(rnum, p, -r);

        fmpz_set(rden, q);
        
        return;
    }

    /*
    We want to compute p/q - r/1 where the inputs are already
    in canonical form.

    Note (p - q*r, q) is in canonical form.

    */
    
    fmpz_init(u);

    fmpz_mul_si(u, q, r);
    fmpz_sub(rnum, p, u);
    fmpz_set(rden, q);

    fmpz_clear(u);
}

void fmpq_sub_si(fmpq_t res, const fmpq_t op1, slong c)
{
    _fmpq_sub_si(fmpq_numref(res), fmpq_denref(res),
              fmpq_numref(op1), fmpq_denref(op1), c);
}
