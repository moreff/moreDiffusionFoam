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

Application
    Test-Function2

Description
    Tests Function2

\*---------------------------------------------------------------------------*/

#include "Function2.H"
#include "IFstream.H"
#include "OFstream.H"
#include "ListOps.H"
#include "argList.H"

using namespace Foam;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
    argList::validArgs.append("dictionary");
    argList args(argc, argv);
    const word dictName(args[1]);
    Info<< "Reading " << dictName << nl << endl;
    const dictionary dict = IFstream(dictName)();

    Info<< "Constructing the function\n" << endl;
    const autoPtr<Function2<scalar>> functionPtr =
        Function2<scalar>::New("function", dict);
    const Function2<scalar>& function = functionPtr();

    const scalar x0 = dict.lookup<scalar>("x0");
    const scalar x1 = dict.lookup<scalar>("x1");
    const label nX = dict.lookup<label>("nX");
    const scalar dx = (x1 - x0)/(nX - 1);
    const scalarField xs
    (
        x0 + dx*List<scalar>(identity(nX))
    );

    const scalar y0 = dict.lookup<scalar>("y0");
    const scalar y1 = dict.lookup<scalar>("y1");
    const label nY = dict.lookup<label>("nY");
    const scalar dy = (y1 - y0)/(nY - 1);
    const scalarField ys
    (
        y0 + dy*List<scalar>(identity(nY))
    );

    OFstream dataFile(dictName + ".dat");
    Info<< "Calculating values and writing to " << dataFile.name() << "\n" << endl;
    dataFile<< "# x y value" << endl;
    forAll(xs, i)
    {
        forAll(ys, j)
        {
            const scalar value = function.value(xs[i], ys[j]);
            dataFile
                << xs[i] << ' '
                << ys[j] << ' '
                << value << endl;
        }
    }

    Info<< "End\n" << endl;

    return 0;
}


// ************************************************************************* //
