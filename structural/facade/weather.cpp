#include <iostream>
#include <string>
#include <tuple>

using namespace std;

class WorldWeatherAPI
{
public:
    tuple<float, float, string> getWeather(string location)
    {
        cout << "Calling worldWeather with location: " << location << endl;
        float temperature = 20.0f;
        float windSpeed = 5.5f;
        string shortDescription = "Sunny";
        return make_tuple(temperature, windSpeed, shortDescription);
    }
};

class FreeWeather
{
public:
    tuple<float, string> retrieve_weather(string location)
    {
        cout << "Calling freeWeather with location: " << location << endl;
        float temperature = 22.0f;
        string shortDescription = "Sunny";
        return make_tuple(temperature, shortDescription);
    }
};

class RealtimeWeatherService
{
public:
    tuple<float, float, string> weatherConditions(string location)
    {
        cout << "Calling realtimeWeather with location: " << location << endl;
        float temperature = 19.5f;
        float humidity = 60.0f;
        string shortDescription = "Partly cloudy with a chance of rain";
        return make_tuple(temperature, humidity, shortDescription);
    }
};

class Weather: public WorldWeatherAPI, public FreeWeather, public RealtimeWeatherService{
public:
    tuple<float, float, string> currentWeather(const string &loc){
        auto worldweatherapi = WorldWeatherAPI::getWeather(loc);
        auto freeweather = FreeWeather::retrieve_weather(loc);
        auto realtimeweatherservice = RealtimeWeatherService::weatherConditions(loc);

        return make_tuple(std::get<0>(worldweatherapi) , std::get<1>(realtimeweatherservice), std::get<1>(freeweather));
    }
};

int main()
{
/*
    WorldWeatherAPI worldWeather;
    FreeWeather freeWeather;
    RealtimeWeatherService realtimeWeather;

    auto const location = "San Francisco, CA, US";
    // Call each API and combine the results
    tuple<float, float, string> worldWeatherResult = worldWeather.getWeather(location);
    tuple<float, string> freeWeatherResult = freeWeather.retrieve_weather(location);
    tuple<float, float, string> realtimeWeatherResult = realtimeWeather.weatherConditions(location);

    // Combine the results into a single string
    float temperature = get<0>(worldWeatherResult);
    float humidity = get<1>(realtimeWeatherResult);
    string shortDescription = get<1>(freeWeatherResult);

    cout << "\nWeather for " << location << endl
         << shortDescription << endl
         << "Temperature: " << temperature << " C" << endl
         << "Humidity: " << humidity << " %" << endl;

    cout<< "Facade class:"<<endl;
*/
    auto const location = "San Francisco, CA, US";
    Weather weather;

    auto weatherResult = weather.currentWeather(location);
    cout << "\nWeather for " << location << endl
         << get<2>(weatherResult) << endl
         << "Temperature: " << get<1>(weatherResult) << " C" << endl
         << "Humidity: " << get<0>(weatherResult) << " %" << endl;

    return 0;
}