import logging
from math import pi as math_pi
import sympy as sp


class BeamTheory():
    def __init__(self, *, youngsModulus=None, lengthOfBeam=None, data=None):
        logging.debug('Creating BeamTheory object.')

        if not lengthOfBeam:
            e = 'Length of beam was not given.'
            logging.error(e)
            raise TypeError(e)
        
        self.L = lengthOfBeam
        self.I = self.calculate_moment_of_inertia(self.L)        
        self.E = youngsModulus
        self.data = data

    def set_data(self, data) -> None:
        self.data = data
        return

    def calculate_moment_of_inertia(self, lengthOfBeam, diameter=None):
        """Calculates the moment of inertia of a uniform cylindrical object.
        
        lengthOfBeam in mm.
        diameter in mm.

        Returns: moment of inertia in g*mm**2.
        """
        # TODO add in diameter, density and volume options.
        logging.debug('Calculating moment of inertia.')

        if not lengthOfBeam:
            e = 'Length of beam was not given.'
            logging.error(e)
            raise TypeError(e)
        
        # TODO add guarding against other inputs.
        # TODO allow usage of diameter
        moment_of_inertia = (1/3) * self._calculate_cyclinder_mass(volume=2816.24) * lengthOfBeam**2
        return moment_of_inertia

    def _calculate_cyclinder_mass(self, volume=None, length=None, diameter=None, density=0.00124):
        """Calculates the mass of a uniform cylinder (whisker).

        Must pass in (Volume) or (Length and Diameter) and (Density).
        Volume in mm**3.
        Length in mm.
        Diameter in mm.
        Density in g/mm**3. Default 0.00124 g/mm**3 for PLA.

        Returns: mass of uniform cylinder in grams.
        """
        # density = 0.00124 as per https://all3dp.com/2/pla-density-what-s-the-density-of-pla-filament-plastic/
        flag_use_volume = False

        if volume and (length or diameter):
            logging.info('Both volume and length or diameter were given. Using volume to calculate mass.')
            flag_use_volume = True

        if (not flag_use_volume) and (not length) and (not diameter):
            e = 'Neither length nor diameter was given.'
            logging.error(e)
            raise TypeError(e)

        if flag_use_volume:
            cylinder_mass = density * volume
        else:
            cylinder_mass = density * math_pi * (diameter/2)**2 * length

        return cylinder_mass
    
    def equation(self):
        # Define the symbols.
        x, L, P, E, I = sp.symbols('x L P E I')

        # Define the deflection function.
        y = sp.Function('y')(x)

        # Define the distributed load.
        w = P

        # Define the differential equation for the beam deflection.
        diff_eq = sp.Eq(sp.diff(E*I*sp.diff(y, x, x), x, x), -w)

        # Solve the differential equation.
        deflection = sp.dsolve(diff_eq, y)
        
        
   

def main() -> None:
    logging.basicConfig(
        level=logging.DEBUG,  # DEBUG, INFO, WARNING, ERROR, CRITICAL
        format="%(asctime)s %(levelname)s %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
        #filename="basic.log",
    )

    BT = BeamTheory(youngsModulus=5, lengthOfBeam=100)
    return


if __name__ == "__main__":
    main()