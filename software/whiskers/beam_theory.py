import logging
from math import pi as math_pi
import sympy as sp
from sympy.physics.continuum_mechanics.beam import Beam


class BeamTheory():
    def __init__(self, *, youngsModulus=None, lengthOfBeam=None, data=None):
        """TODO

        youngsModulus in GPa.
        TODO
        """
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
        logging.debug(f'Calculated moment of inertia={moment_of_inertia}')
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

        if volume: 
            flag_use_volume = True
        if volume and (length or diameter):
            logging.info('Both volume and length or diameter were given. Using volume to calculate mass.')
            

        if (not flag_use_volume) and (not length) and (not diameter):
            e = 'Neither length nor diameter was given.'
            logging.error(e)
            raise TypeError(e)

        if flag_use_volume:
            logging.debug('Using volume to calculate cylinder mass.')
            cylinder_mass = density * volume
        else:
            logging.debug('Using length and diameter to calculate cylinder mass.')
            cylinder_mass = density * math_pi * (diameter/2)**2 * length
        logging.debug(f'Calculated mass={cylinder_mass}')
        return cylinder_mass
    
    def equation(self):
        logging.info('Starting equation')
        force = 10
        D = sp.symbols('D')
        polynomialOrder = 1  # I don't know what this is.

        beam = Beam(self.L, self.E, self.I)
        beam.apply_load(force, D, polynomialOrder)
        beam.solve_for_reaction_loads(D)
        logging.debug('Should now plot bending moment.')
        beam.plot_bending_moment()

        return

    def equation2(self):
        logging.info(f'Starting equation2')
        # Define the symbols.
        x, L, P, E, I = sp.symbols('x L P E I')

        # Define the deflection function.
        y = sp.Function('y')(x)

        # Define the distributed load.
        w = P
        
        E = self.E
        I = self.I
        w = 10


        # Define the differential equation for the beam deflection.
        diff_eq = sp.Eq(sp.diff(E*I*sp.diff(y, x, x), x, x), -w)

        # Solve the differential equation.
        deflection = sp.dsolve(diff_eq, y)
        return deflection
    
    def calculate_deflection(x, L, F, E, I):
        """
        Calculate the deflection of a beam using the Euler-Bernoulli beam theory.

        Parameters:
        - x: Position along the beam
        - L: Length of the beam
        - F: Applied load
        - E: Modulus of elasticity
        - I: Moment of inertia

        Returns:
        - Deflection at position x
        """
        logging.info(f'Starting calculate_deflection')
        deflection = (F * x * (6 * L**2 - 4 * x**2)) / (24 * E * I)
        return deflection
        # Example usage:
        L = 10.0          # Length of the beam
        F = 100.0         # Applied load
        E = 200000.0      # Modulus of elasticity
        I = 100.0         # Moment of inertia
        x_position = 5.0  # Position along the beam
        deflection_at_x = calculate_deflection(x_position, L, F, E, I)
        print(f"The deflection at x = {x_position} is {deflection_at_x:.4f} units.")
    
        
def configuration() -> None:
    # Logging.
    logging.basicConfig(
        level=logging.DEBUG,  # DEBUG, INFO, WARNING, ERROR, CRITICAL
        format="%(asctime)s %(levelname)s %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
        #filename="basic.log",
    )

    # sympy.
    sp.init_printing(use_unicode=True)
    return


def main() -> None:
    configuration()

    BT = BeamTheory(youngsModulus=4.107, lengthOfBeam=150)
    print(BT.equation2())

    return


if __name__ == "__main__":
    main()
