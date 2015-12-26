#include <iostream>
#include <map>

namespace mungebits {
  class Datum {
    virtual void* serialize() = 0;
  };

  class DoublerDatum : public Datum {
  public:
    void* serialize() {
      void* x = malloc(sizeof(double));
      memcpy(x, &this->coefficient, sizeof(double));
      return x;
    }

    DoublerDatum(double coeff) : coefficient(coeff) { }

  private:
    double coefficient;
  };
}

int main(int argc, char** argv) {
  mungebits::DoublerDatum datum = mungebits::DoublerDatum(2.5);
  double* out = (double*)datum.serialize();
  std::cout << *out << std::endl;
  return 0;
}


