/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | moreDiffusionFoam: Useful tools and tutorials for
   \\    /   O peration     |         diffusion modelling in OpenFOAM
    \\  /    A nd           | Website: github.com/moreff/moreDiffusionFoam
     \\/     M anipulation  | 2022 Ilya Morev
-------------------------------------------------------------------------------
License
    This file is part of moreDiffusionFoam library, derived from OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

#include "binaryDiffusionCoefficientsPolynomial.H"
#include "addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace Function2s
{
    makeScalarFunction2(binaryDiffusionCoefficientsPolynomial)
}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::Function2s::binaryDiffusionCoefficientsPolynomial::binaryDiffusionCoefficientsPolynomial
(
    const word& name,
    const FixedList<scalar, 5> polynomialCoeffs
)
:
    FieldFunction2<scalar, binaryDiffusionCoefficientsPolynomial>(name),
    polynomialCoeffs_(polynomialCoeffs)
{}


Foam::Function2s::binaryDiffusionCoefficientsPolynomial::binaryDiffusionCoefficientsPolynomial
(
    const word& name,
    const dictionary& dict
)
:
    FieldFunction2<scalar, binaryDiffusionCoefficientsPolynomial>(name),
    polynomialCoeffs_(dict.lookup<FixedList<scalar, 5>>("polynomialCoeffs"))
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void Foam::Function2s::binaryDiffusionCoefficientsPolynomial::write(Ostream& os) const
{
    writeEntry(os, "polynomialCoeffs", polynomialCoeffs_);
}


// ************************************************************************* //
