//https://stackoverflow.com/questions/9905093/how-to-check-whether-two-matrices-are-identical-in-opencv

//1
// Get a matrix with non-zero values at points where the 
// two matrices have different values
cv::Mat diff = a != b;
// Equal if no elements disagree
bool eq = cv::countNonZero(diff) == 0;

//2
bool eq = std::equal(a.begin<uchar>(), a.end<uchar>(), b.begin<uchar>());

//3
bool isEqual = (sum(img1 != img2) == Scalar(0,0,0,0));

//4

bool matIsEqual(const cv::Mat Mat1, const cv::Mat Mat2)
{
  if( Mat1.dims == Mat2.dims && 
    Mat1.size == Mat2.size && 
    Mat1.elemSize() == Mat2.elemSize())
  {
    if( Mat1.isContinuous() && Mat2.isContinuous())
    {
      return 0==memcmp( Mat1.ptr(), Mat2.ptr(), Mat1.total()*Mat1.elemSize());
    }
    else
    {
      const cv::Mat* arrays[] = {&Mat1, &Mat2, 0};
      uchar* ptrs[2];
      cv::NAryMatIterator it( arrays, ptrs, 2);
      for(unsigned int p = 0; p < it.nplanes; p++, ++it)
        if( 0!=memcmp( it.ptrs[0], it.ptrs[1], it.size*Mat1.elemSize()) )
          return false;

      return true;
    }
  }

  return false;
}
