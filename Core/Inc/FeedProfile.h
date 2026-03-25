/* Nutrient Feed Profile
*	
*/

typedef struct{
	float floraMicro_ml_per_gal;
	float floraGrow_ml_per_gal;
	float floraBloom_ml_per_gal;
	float targetEC;
	float ECRange;
	float targetPH;
    float phRange;
}FeedProfile;

 //Format: FeedProfile newProfile = {micro(mL/gal),grow(mL/gal),bloom(mL/gal),EC,ECRangeOfError, pH, pHRangeOfError}