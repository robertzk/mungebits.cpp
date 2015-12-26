#include <iostream>
#include <map>

namespace mungebits {
  class Datum {
    virtual void* serialize() = 0;
  };

  class MultiplierDatum : public Datum {
  public:
    void* serialize() {
      void* x = malloc(sizeof(double));
      memcpy(x, &this->coefficient, sizeof(double));
      return x;
    }

    MultiplierDatum(const double coeff) : coefficient(coeff) { }

    const double getCoefficient() const { return this->coefficient; }

  private:
    const double coefficient;
  };
}

int main(int argc, char** argv) {
  mungebits::MultiplierDatum datum = mungebits::MultiplierDatum(2.5);
  double* out = (double*)datum.serialize();
  std::cout << *out << std::endl;
  std::cout << datum.getCoefficient() << std::endl;
  return 0;
}


