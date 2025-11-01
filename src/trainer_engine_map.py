import math
from enum import Enum


class Propeller(Enum):
    P12x6 = 0
    P13x65 = 1
    P13x8 = 2
    P14X85 = 3
    P15x7 = 4
    P15x8 = 5
    UNDEF1 = 6
    UNDEF2 = 7

class EngineMap:
    def __init__(self, propeller=None):
        self.propeller = propeller
        self.valid_propeller = True
        self._max_current = 40  # Amps
        self._max_windspeed = 30  # m/s
    
    def thrust_of_windspeed_current(self, windspeed, current):
        if current > self._max_current:
            raise ValueError(f"Current exceeds maximum of {self._max_current} Amps")
        if windspeed > self._max_windspeed:
            raise ValueError(f"Windspeed exceeds maximum of {self._max_windspeed} m/s")
        x = windspeed
        y = current
        
        # coefficients from matlab interpolation with 95% confidence bounds
        p00 = p10 = p01 = p20 = p11 = p02 = 0.0

        if self.propeller == Propeller.P12x6:
            p00 = 0.157
            p10 = -0.1252
            p01 = 0.848
            p20 = -0.004118
            p11 = -0.0116
            p02 = -0.007223
        elif self.propeller == Propeller.P13x65:
            p00 = 0.5261
            p10 = -0.1959
            p01 = 0.8247
            p20 = -0.002268
            p11 = -0.01013
            p02 = -0.00622
        elif self.propeller == Propeller.P13x8:
            p00 = 0.4304
            p10 = -0.1456
            p01 = 0.7532
            p20 = -0.003073
            p11 = -0.00794
            p02 = -0.005196
        elif self.propeller == Propeller.P14X85:
            p00 = 0.714
            p10 = -0.1716
            p01 = 0.7453
            p20 = -0.003225
            p11 = -0.008028
            p02 = -0.004771
        elif self.propeller == Propeller.P15x7:
            p00 = 0.9626
            p10 = -0.2855
            p01 = 0.8439
            p20 = -0.002084
            p11 = -0.01075
            p02 = -0.005737
        elif self.propeller == Propeller.P15x8:
            p00 = 1.127
            p10 = -0.2072
            p01 = 0.757
            p20 = -0.003704
            p11 = -0.00825
            p02 = -0.004828
        else:
            print(f"ERROR: prop {self.propeller} is unknown")
            self.valid_propeller = False
            return 0.0

        return (p00 + p10 * x + p01 * y + p20 * math.pow(x, 2) + 
                p11 * x * y + p02 * math.pow(y, 2))


    def power_of_windspeed_current(self, windspeed, current):
        if current > self._max_current:
            raise ValueError(f"Current exceeds maximum of {self._max_current} Amps")
        if windspeed > self._max_windspeed:
            raise ValueError(f"Windspeed exceeds maximum of {self._max_windspeed} m/s")
        x = windspeed
        y = current
        # coefficients from matlab interpolation with 95% confidence bounds
        p00 = p10 = p01 = p20 = p11 = p02 = 0.0

        if self.propeller == Propeller.P12x6:
            p00 = 0.0101
            p10 = -0.09204
            p01 = 12.57
            p20 = 0.004521
            p11 = -0.03717
            p02 = -0.05455
        elif self.propeller == Propeller.P13x65:
            p00 = 2.333
            p10 = -0.6026
            p01 = 12.03
            p20 = 0.02185
            p11 = 0.01025
            p02 = -0.0493
        elif self.propeller == Propeller.P13x8:
            p00 = 0.973
            p10 = -0.0912
            p01 = 11.57
            p20 = 0.00196
            p11 = 0.01271
            p02 = -0.03881
        elif self.propeller == Propeller.P14X85:
            p00 = -1.808
            p10 = 0.6065
            p01 = 11.5
            p20 = -0.01986
            p11 = 0.002315
            p02 = -0.03478
        elif self.propeller == Propeller.P15x7:
            p00 = 4.403
            p10 = -1.364
            p01 = 12.18
            p20 = 0.05301
            p11 = -0.0008103
            p02 = -0.04432
        elif self.propeller == Propeller.P15x8:
            p00 = -0.4518
            p10 = 0.6766
            p01 = 11.41
            p20 = -0.02981
            p11 = 0.01263
            p02 = -0.04048
        else:
            print(f"ERROR: prop {self.propeller} is unknown")
            return 0.0

        return (p00 + p10 * x + p01 * y + p20 * math.pow(x, 2) + 
                p11 * x * y + p02 * math.pow(y, 2))


# Import the EngineMap class and Propeller enum class
# from engine_map_acc24 import EngineMap, Propeller

# Create an instance of EngineMap with a specific propeller (by typing Propeller. you will see the options)
engine = EngineMap(Propeller.P12x6)


# Calculate thrust for a given operating point
windspeed = 10.0 # [m/s]
current = 35.0    # [A]
thrust = engine.thrust_of_windspeed_current(windspeed, current) # [N]

print(f"Thrust {thrust:0.2f} N @ {windspeed} m/s windspeed and {current} Amps current")