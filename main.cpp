#include <string>
#include <cmath>
#include <iostream>
#include <cstdlib>

class Field  //create class Field
{
    protected:  //create protected variable
        double *value;  //pointer to array of 3 doubles

    public:  //create public variables section
        Field()  //create default Field constructor
            { value = new double[3]{0.0, 0.0, 0.0}; }  //default x,y,z values to zero

        Field(double xVal, double yVal, double zVal)  //create Parameters constructor
            { value = new double[3]{xVal, yVal, zVal}; }  //allocate memory and assign supplied x, y and z values

        Field(const Field& other)  //create copying constructor
        {
            value = new double[3];  //allocate memory
            value[0] = other.value[0];  //copy x component
            value[1] = other.value[1];  //copy y component
            value[2] = other.value[2];  //copy z component
        }

        void setX(double xVal)  //establish set function for X value
            { value[0] = xVal; }  //set X to xVal

        void setY(double yVal)  //establish set function for Y value
            { value[1] = yVal; }  //set y to yVal

        void setZ(double zVal)  //establish set function for Z value
            { value[2] = zVal; }  //set z to zVal

        double getX() const  //establish get function for X value
            { return value[0]; }  //return the current value of X

        double getY() const  //establish get function for Y value
            { return value[1]; }  //return the current value of Y

        double getZ() const  //establish get function for Z value
            { return value[2]; }  //return the curent value of Z

        double calculateMagnitude() const  //function to calculate vector magnitude
            { return std::sqrt(value[0] * value[0] + value[1] * value[1] + value[2] * value[2]); }  //return sqrt sum of squares

        double calculateInnerProduct() const  //function to calculate inner product
            { return (value[0] * value[0] + value[1] * value[1] + value[2] * value[2]); }  //return dot product

        void printMagnitude() const  //function to print components and magnitude
        {
            std::cout << "Components: " << value[0] << ", " << value[1] << ", " << value[2] << std::endl;  //output components
            std::cout << "Magnitude: " << calculateMagnitude() << std::endl;  //output magnitude
        }

        virtual ~Field()  //create a destructor
            { delete[] value; }  //free the allocated memory
};

class Electric_Field : public Field  //create derived class for Efield inheriting from Field
{
    private:  //create private variables section
        double calculatedEField;  //variable to store calculated electric field

    public:  //create public variables section
        Electric_Field() : Field()  //create default Efield constructor calling base default
            { calculatedEField = 0.0; }  //default calculated Efield to zero

        Electric_Field(double xVal, double yVal, double zVal) : Field(xVal, yVal, zVal)  //create parameters constructor calling base constructor
            { calculatedEField = 0.0; }  //default calculated Efield to zero

        Electric_Field(const Electric_Field& other) : Field(other)  //create copy constructor calling base copy constructor
            { calculatedEField = other.calculatedEField; }  //copy calculated Efield value

        void calculateElectricField(double Q, double r)  //function to calculate E-field via Gausses Law
        {
            const double EPSILON_0 = 8.854187817e-12;  //permittivity of free space in F/m
            if (r == 0.0)  //check if distance r is zero
                { std::cout << "Distance r is zero, electric field is undefined." << std::endl; }  //print undefined message
            else
                { calculatedEField = Q / (4.0 * M_PI * r * r * EPSILON_0); }  //compute E-field magnitude
        }

        double getCalculatedEField() const  //establish get function for calculated E-field
            { return calculatedEField; }  //return calculated E-field value

        Electric_Field operator+(const Electric_Field& other) const  //overload + operator for two Electric_Field objects
        {
            Electric_Field result(this->value[0] + other.value[0], this->value[1] + other.value[1], this->value[2] + other.value[2]);  //create sum object
            return result;  //return new combined electric field object
        }

        friend std::ostream& operator<<(std::ostream& os, const Electric_Field& eField)  //overload << operator for stream output
        {
            os << eField.value[0] << ", " << eField.value[1] << ", " << eField.value[2];  //format output stream
            return os;  //return output stream
        }

        virtual ~Electric_Field()  //create a destructor
            {}  //memory freed by base class destructor
};

class Magnetic_Field : public Field  //create derived class for Mfield inheriting from Field
{
    private:  //create private variables section
        double calculatedBField;  //variable to store calculated magnetic field

    public: //create public variables section
        Magnetic_Field() : Field()  //create default Mfield constructor calling base default
            { calculatedBField = 0.0; }  //default calculated Bfield to zero

        Magnetic_Field(double xVal, double yVal, double zVal) : Field(xVal, yVal, zVal)  //create parameters constructor calling base constructor
            { calculatedBField = 0.0; }  //default calculated Bfield to zero

        Magnetic_Field(const Magnetic_Field& other) : Field(other)  //create copy constructor calling base copy constructor
            { calculatedBField = other.calculatedBField; }  //copy calculated Bfield value

        void calculateMagneticField(double I, double r)  //function to calculate B-field via Ampere's Law
        {
            const double MU_0 = 4.0 * M_PI * 1e-7;  //permeability of free space in T*m/A
            if (r == 0.0)  //check if distance r is zero
                { std::cout << "Distance r is zero, undefined magnetic field." << std::endl; }  //print undefined message
            else
                { calculatedBField = (MU_0 * I) / (2.0 * M_PI * r); }  //compute Bfield magnitude
        }

        double getCalculatedBField() const  //establish get function for calculated B-field
            { return calculatedBField; }  //return calculated B-field value

        void calculateUnitVector() const  //function to calculate unit vector
        {
            double mag = calculateMagnitude();  //calculate magnitude of current vector
            if (mag == 0.0)  //check if magnitude is zero
                { std::cout << "Magnitude is zero, unit vector is undefined\n." << std::endl; }  //print undefined message
            else
                { std::cout << (value[0] / mag) << ", " << (value[1] / mag) << ", " << (value[2] / mag) << "\n" << std::endl; }  //print components
        }

        Magnetic_Field operator+(const Magnetic_Field& other) const  //overload + operator for 2 Magnetic_Field objects
        {
            Magnetic_Field result(this->value[0] + other.value[0], this->value[1] + other.value[1], this->value[2] + other.value[2]);  //create sum object
            return result;  //return magnetic field object
        }

        friend std::ostream& operator<<(std::ostream& os, const Magnetic_Field& bField)  //overload << operator output
        {
            os << bField.value[0] << ", " << bField.value[1] << ", " << bField.value[2];  //format output stream
            return os;  //return output stream
        }

        virtual ~Magnetic_Field()  //create a destructor
            {}  //memory freed by destructor
};

int main(int argc, char* argv[])  //main using the user inputs
{
    if (argc != 4)  //verify user gave input 3 values
    {
        std::cout << "\nInvalid number of arguments. Aborting" << std::endl;  //output argument count error
        return 1;  //abort program execution
    }

    double xInput = std::atof(argv[1]);  //convert argv[1] to double for x value
    double yInput = std::atof(argv[2]);  //convert argv[2] to double for y value
    double zInput = std::atof(argv[3]);  //convert argv[3] to double for z value

    if ((xInput == 0.0 && argv[1][0] != '0') || (yInput == 0.0 && argv[2][0] != '0') || (zInput == 0.0 && argv[3][0] != '0'))  //check user entries are valid values
    {
        std::cout << "\nArguments must be valid numbers, Aborting." << std::endl;  //output user input error
        return 1;  //abort program execution
    }

    Electric_Field eFieldDefault;  //create default Efield object

    eFieldDefault.setX(xInput);  //set X value
    eFieldDefault.setY(yInput);  //set Y value
    eFieldDefault.setZ(zInput);  //set Z value

    std::cout << "\nComponents: " << eFieldDefault.getX() << ", " << eFieldDefault.getY() << ", " << eFieldDefault.getZ() << std::endl;  //output electric field components
    std::cout << "\n*** Electric Field (Default + Setters) ***" << std::endl;  //output efield header
    std::cout << "Electric Field Magnitude: " << eFieldDefault.calculateMagnitude() << std::endl;  //output Efield magnitude
    std::cout << "Electric Field Inner Product: " << eFieldDefault.calculateInnerProduct() << std::endl;  //output Efield inner product

    Electric_Field eFieldComp(1e5, 10.9, 1.7e2);  //create Efield object using 3-component constructor
    std::cout << "\n*** Electric Field (Component Constructor) ***" << std::endl;  //output efield component header
    eFieldComp.printMagnitude();  //print components and magnitude
    std::cout << "Electric Field Inner Product: " << eFieldComp.calculateInnerProduct() << std::endl;  //output the Efield inner product

    double chargeQ = 5.0e-6;  //define charge Q in Coulombs
    double distE = 0.05;  //define distance r in meters
    eFieldComp.calculateElectricField(chargeQ, distE);  //calculate electric field using Gausses Law
    std::cout << "Gauss' Law Electric Field: " << eFieldComp.getCalculatedEField() << " N/C" << std::endl;  //output Gausses Law result

    std::cout << "\n*** Magnetic Field (Component Constructor) ***" << std::endl;  //output Mfield section header
    Magnetic_Field mFieldComp(xInput, yInput, zInput);  //create mfield with input parameters

    mFieldComp.printMagnitude();  //print components and magnitude using inherited base method
    std::cout << "Magnetic Field Unit Vector: ";  //output label for unit vector
    mFieldComp.calculateUnitVector();  //calculate and output unit vector

    double currentI = 10.0;  //define current I in Amps
    double distB = 0.02;  //define distance r in meters
    mFieldComp.calculateMagneticField(currentI, distB);  //calculate magnetic field using ampere's Law
    std::cout << "Ampere's Law Magnetic Field: " << mFieldComp.getCalculatedBField() << " T" << std::endl;  //output result

    Magnetic_Field mFieldDefault;  //create default Mfield object
    mFieldDefault.setX(xInput);  //set X value for default Mfield
    mFieldDefault.setY(yInput);  //set Y value for default Mfield
    mFieldDefault.setZ(zInput);  //set Z value for default Mfield

    std::cout << "\n*** Magnetic Field (Default + Setters) ***" << std::endl;  //output Mfield header
    std::cout << "Magnetic Field Magnitude: " << mFieldDefault.calculateMagnitude() << std::endl;  //output Mfield magnitude for default constructor
    std::cout << "Magnetic Field Unit Vector: ";  //output label for unit vector
    mFieldDefault.calculateUnitVector();  //calculate and output unit vector for default constructor

    std::cout << "*** Operator Overloading (+ and <<) ***" << std::endl;
    Electric_Field eFieldSum = eFieldDefault + eFieldComp;
    std::cout << "Electric Field 1: " << eFieldDefault << std::endl;
    std::cout << "Electric Field 2: " << eFieldComp << std::endl;
    std::cout << "Electric Field Sum (E1 + E2): " << eFieldSum << std::endl;

    Magnetic_Field mField2(1.0, 2.0, 3.0);
    Magnetic_Field mFieldSum = mFieldComp + mField2;
    std::cout << "\nMagnetic Field 1: " << mFieldComp << std::endl;
    std::cout << "Magnetic Field 2: " << mField2 << std::endl;
    std::cout << "Magnetic Field Sum (B1 + B2): " << mFieldSum << "\n" << std::endl;

    return 0;  //return zero to exit
}

