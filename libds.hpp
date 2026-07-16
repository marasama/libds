#pragma once

class libds {
  public:
    libds();
    ~libds();

  /* Z Score Normalization  
   *
   double val = 1, mean = 3, std, 2;
   double norm = z_score_norm(val, mean, std);*/
  template <typename A>
  static A z_score_norm(A val, A mean, A std){return (val - mean) / std;}
  /* Z Score Denormalization  
   *
   double val = 1, mean = 3, std, 2;
   double norm = z_score_norm(val, mean, std);
   double denorm = z_score_denorm(norm, mean, std);*/
  template <typename A>
  static A z_score_denorm(A val, A mean, A std){return std * val + mean;};
  ///
};
