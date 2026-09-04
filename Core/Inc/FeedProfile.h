#ifndef FEEDPROFILE_H
#define FEEDPROFILE_H

typedef struct {
  float floraMicro_ml_per_gal;
  float floraGrow_ml_per_gal;
  float floraBloom_ml_per_gal;
  float targetEC;
  float ECRange;
  float targetPH;
  float phRange;
} FeedProfile;

/* Indexed by enum growthStage */
extern const FeedProfile lightFeedProfile[];
extern const FeedProfile mediumFeedProfile[];

#endif /* FEEDPROFILE_H */
