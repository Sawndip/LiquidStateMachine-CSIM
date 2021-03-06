/** \file discretizationpreprocessor.h
**  \brief Implementation of a discretization of the input.
*/

#ifndef _DISCRETIZATIONPREPROCESSOR_H_
#define _DISCRETIZATIONPREPROCESSOR_H_

#include <string>
#include <map>
#include <list>
#include "preprocessor.h"
#include "csimerror.h"

using namespace std;

//!  Implementation of a discretization of the input. Every row x_i of the input vector is transformed into \f$x_i' = round (x_i / \epsilon_i)\f$.
class DiscretizationPreprocessor : public Preprocessor {

  DO_REGISTERING

 public:
  /** Constructs a new discretization. Initially the transformation is an identical transformation x'=x. 
      \param rows Number of rows in each input vector. */
  DiscretizationPreprocessor(unsigned int rows = 1);

  ~DiscretizationPreprocessor(void);

  /** Preprocess a state representation.
      \param S State of the liquid (= filtered response of the neural microcircuit).
      \param X Target vector where to save the results. 
      \return -1 if an error occured, 1 for success. */
  int process(const double* S, double* X);

  /** Resets the information stored within the preprocessor. */
  void reset();

  /** Imports the data from an externally (e.g. Matlab) trained preprocessor.
      \param rep Representation of the preprocessor as a double vector. 
      Format: first number gives the number of rows for input vectors, the following rows elements are
      in the format [eps_1, eps_2, ..., eps_n], where the transformations are \f$round(x_i / eps_i)\f$.
      \param rep_length Length of the representation vector.
      \return -1 if an error occured, 1 for success. */
  int importRepresentation(const double* rep, int rep_length);

  /** Exports the representation of this preprocessor for use in external objects.
      Format: first number gives the number of rows for input vectors, the following rows elements are
      in the format [eps_1, eps_2, ..., eps_n], where the transformations are \f$round(x_i / eps_i)\f$.
      \param rep_length Length of the representation vector.
      \return A list of parameters that represent the preprocessor. 
      \warning Do not forget to free the memory reserved for the representation! */
  double* exportRepresentation(int *rep_length);

  /** Returns a textual description of the representation format for import/export - Representation. */
  string getFormatDescription();

 private:

  //! The parameters of the discretization.
  double *epsilon;
  
};

#endif
