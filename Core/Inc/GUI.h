#ifndef GUI_H
#define GUI_H

#define BUFFER_LINES 60

void initScreen(void);
void uiInitScreens(void);

void setTemperature(float c);
void setWaterLevel(float percent);
void setNutrientDensity(float ec);
void setPlantInfo(const char *name, const char *stage);
#endif // !GUI_H
