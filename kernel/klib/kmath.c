/*
LFOS, a simple operating system.
Copyright (C) 2016 LFUnion.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// mathematical basic functions

#include "kmath.h"

#define maxfractions1 50

#define maxfractions2 60

#define recursion 50

double abs(const double value){
    double rvalue = -value;
    
    if (value >0){
        return value;
        
    }	
    return rvalue;
}

uint64_t abs_i(int64_t value){
    return (value>0? value : -value);
}

double pow( const double base, const double exponent){	

    double end_value = 1;
    int64_t exponent_long = (int64_t) exponent;
    
    if(exponent > 0){
        if (exponent_long == exponent){
            for (int64_t c = 0; c<exponent_long ;++c){
                end_value = base * end_value;
            }
            return end_value;
        }
        else{
            const double rroot = 1.0 / (exponent -(double) exponent_long);
            for (int64_t c = 0; c<exponent_long ;++c){
                end_value = base * end_value;
            }
            end_value = root(base, rroot) * end_value;
            
        }
    }

    else if(exponent < 0){
        if (exponent_long == exponent){
            for (int64_t c = 0; c>exponent_long ;--c){
                end_value = end_value / base;
            }
            return end_value;
        }
        else{
            const double rroot = -(1.0 / (exponent -(double) exponent_long));
            for (int64_t c = 0; c>exponent_long ;--c){
                end_value = end_value / base;
            }
            
            end_value =  end_value / root(base, rroot);
            
        }
    }
    
    return end_value;	
}

double pow_i(const double base, const int64_t exponent){
	
    double end_value = 1;
    
    if(exponent>0){
        for (int64_t c = 0; c<exponent ;++c){
            end_value = base * end_value;
        }
    }
    else if(exponent<0){
        for (int64_t c = 0; c>exponent ;--c){
            end_value = end_value / base;
        }
    }
    
    return end_value;
}

// experimental secondroot function
double secondroot (const double radicand){
	if(radicand<=0){
	    return 0;
    }
    
    double end_value;
    int c = 1;
    while (pow_i(c,2)<=radicand){
		++c;
    }
    
    c = c-1;
    
    end_value = c + continuous_fraction_root(c, radicand, maxfractions1);
    return end_value;
}

double continuous_fraction_root(const double minus, const double radicand, uint8_t max){
    if(max ==0){
        return 1;
    }
    
    --max;

    double rvalue = 1/(((minus + minus) + continuous_fraction_root(minus, radicand, max))/(radicand - minus));
    
    return rvalue;
}

double root (const double radicand, double exponent){

    if(exponent<1){
        return pow(radicand, 1.0 / exponent);
    }
    
    double rvalue = radicand;   
    const double exponent_long = round(exponent);
    
    if ((exponent_long+0.0005)>exponent && exponent_long < exponent){
        exponent = exponent_long;
    }

    else if ((exponent_long-0.0005)<exponent && exponent_long > exponent){
        exponent = exponent_long;
    }
    
    const double exponent_low = exponent -1;
    
    for (unsigned int c = 0;c<recursion; ++c){
        rvalue = ((exponent_low)* pow(rvalue, exponent) + radicand)/(exponent * pow(rvalue,exponent_low));
        
    }
    return rvalue;
}

// extern inline
uint64_t round (const double value){
    uint64_t rvalue = (uint64_t) value;
    const double compare = value - rvalue;
    
    if(compare<0.5){
        return rvalue;
        
    }
    else {
       ++rvalue;
       return rvalue; 
    }

}

// extern inline
uint64_t factorial(const int32_t value){
    
    if(value<2){
		if (value<0){
            return 0;
        }   
        else{
            return 1;
        }
    }
    const uint32_t cvalue = value +1;
    
    uint64_t rvalue = 1;
    
    for(int32_t c = 2; c<cvalue; ++c){
        rvalue *= c;

    }
    return rvalue;
}

// pow experimental
double pow_exp(const double base, const double exponent){
        
    double end_value = 1;
    double newbase = base;
    
    int64_t exponent_long = (int64_t) exponent;
    const int64_t exponent_long_check = exponent_long;


    if(exponent_long % 2 == 0){
            exponent_long = exponent/2;
            newbase = newbase * newbase;
    }

    if(exponent_long % 3 == 0){
            exponent_long = exponent/3;
            newbase = newbase * newbase * newbase;        
    }

    if(exponent_long % 5 == 0){
            exponent_long = exponent/5;
            newbase = newbase * newbase * newbase * newbase * newbase;
    }
        

    if(exponent > 0){

        if (exponent_long_check == exponent){
            for (int64_t c = 0; c<exponent_long ;++c){
                end_value = newbase * end_value;
            }
            
            return end_value;
        }
        
        else{
            const double rroot = 1.0 / (exponent -(double) exponent_long_check);
            
            for (int64_t c = 0; c<exponent_long ;++c){
                end_value = newbase * end_value;
            }
            end_value = root(base, rroot) * end_value;
            
        }
    }

    else if (exponent < 0){
        if (exponent_long_check == exponent){
            for (int64_t c = 0; c>exponent_long ;--c){
                end_value = end_value / newbase;
            }
            
            return end_value;
        }
        else{
            const double rroot = -(1.0 / (exponent -(double) exponent_long_check));
            
            for (int64_t c = 0; c>exponent_long ;--c){
                end_value = end_value / newbase;
            }
            
            end_value =  end_value / root(base, rroot);
        }
    }
    
    return end_value;	
}

