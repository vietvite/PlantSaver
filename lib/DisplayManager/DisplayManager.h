#include <Adafruit_SSD1306.h>

class DisplayManager
{
public:
    DisplayManager(Adafruit_SSD1306 &display) : display(display) {}

    void showSoilMoisture(int value, int percent)
    {
        if (percent > 100)
        {
            percent = 100;
        }
        else if (percent < 0)
        {
            percent = 0;
        }

        Serial.print(percent);
        Serial.println(" %");

        display.setCursor(0, 0);
        display.setTextSize(2); // Set text size to 2
        display.setTextColor(WHITE);
        display.print("Val: ");
        display.println(value);

        display.setCursor(0, 20); // Adjust cursor position for larger text size
        display.setTextSize(2);   // Set text size to 2
        display.setTextColor(WHITE);
        display.print("%  : ");
        display.println(percent);

        display.display();
        delay(250);
        display.clearDisplay();
    }

private:
    Adafruit_SSD1306 &display;
};