#include <iostream>
#include <map>
#include <string>
#include <vector>

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

    MultiplierDatum() : coefficient(0) { }
    MultiplierDatum(const double coeff) : coefficient(coeff) { }

    const double getCoefficient() const { return this->coefficient; }

  private:
    double coefficient;
  };


  // template<typename T>
  class Mungebit {
  protected:
    bool  trained; 
    int   input_length;
    void* input;

  public:

    // Functions are responsible for their own serialization and deserialization.
    virtual double* train(const double* data, const size_t &size, const void *train_args) = 0;
    virtual const double* predict(std::vector<double> &data, const void *predict_args) const = 0;

    Mungebit() : trained(false) { }
    ~Mungebit() { std::free(input); }

    bool operator[](int i) { return true; }

  private:
    const Mungebit(Mungebit& m);
  };

  class MultiplierMungebit : public Mungebit {
  public:
    double* train(const double* data, const size_t &size, const void *train_args) {
      this->datum = mungebits::MultiplierDatum(data[0]);
      double* new_data = (double*)std::malloc(sizeof(double) * size);
      const double coeff = this->datum.getCoefficient();
      for (auto i = 0; i < size; ++i) new_data[i] = coeff * data[i];
      return new_data;
    }

    double* predict(std::vector<double> &data, const void *predict_args) const {
      double* output = (double*)std::malloc(sizeof(double) * 10);
      for (auto i = 0; i < 10; ++i) output[i] = (20 - i) / 10.0;
      return output;
    }

    bool operator[](int i) { return true; }

    MultiplierDatum &getDatum() { return this->datum; }

  private:
    MultiplierDatum datum;
  };
}

int main(int argc, char** argv) {
  mungebits::MultiplierMungebit *m = new mungebits::MultiplierMungebit();
  std::vector<double> foo = std::vector<double>(1.0, 2.0);
  const void* pa;
  const double* preds = m->predict(foo, pa); 
  for (auto i = 0; i < 10; ++i) std::cout << preds[i] << std::endl;
  double *new_data = m->train(preds, 10, pa);
  for (auto i = 0; i < 10; ++i) std::cout << new_data[i] << std::endl;
  std::cout << "Coeff: " << m->getDatum().getCoefficient() << std::endl;
  return 0;
}


