/* 
 * File DecStatistic.cxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 
#include "SAFplusTypesCommon.hxx"

#include <vector>
#include "clMgtObject.hxx"
#include "clMgtProv.hxx"
#include "clMgtProvList.hxx"
#include "DecStatistic.hxx"


namespace SAFplusTypes
  {

    DecStatistic::DecStatistic(): SAFplus::ClMgtObject("decStatistic"), current("current"), history10sec("history10sec"), history1min("history1min"), history10min("history10min"), history1hour("history1hour"), history12hour("history12hour"), history1day("history1day"), history1week("history1week"), history1month("history1month")
    {
        this->addChildObject(&current, "current");
        this->addChildObject(&history10sec, "history10sec");
        this->addChildObject(&history1min, "history1min");
        this->addChildObject(&history10min, "history10min");
        this->addChildObject(&history1hour, "history1hour");
        this->addChildObject(&history12hour, "history12hour");
        this->addChildObject(&history1day, "history1day");
        this->addChildObject(&history1week, "history1week");
        this->addChildObject(&history1month, "history1month");
    };

    std::vector<std::string>* DecStatistic::getChildNames()
    {
        std::string childNames[] = { "current", "history10sec", "history1min", "history10min", "history1hour", "history12hour", "history1day", "history1week", "history1month" };
        return new std::vector<std::string> (childNames, childNames + sizeof(childNames) / sizeof(childNames[0]));
    };

    /*
     * XPATH: /SAFplusTypes/decStatistic/current
     */
    long DecStatistic::getCurrent()
    {
        return this->current.Value;
    };

    /*
     * XPATH: /SAFplusTypes/decStatistic/current
     */
    void DecStatistic::setCurrent(long currentValue)
    {
        this->current.Value = currentValue;
    };

    /*
     * XPATH: /SAFplusTypes/decStatistic/history10sec
     */
    std::vector<long> DecStatistic::getHistory10sec()
    {
        return this->history10sec.Value;
    };

    /*
     * XPATH: /SAFplusTypes/decStatistic/history10sec
     */
    void DecStatistic::setHistory10sec(long history10secValue)
    {
        this->history10sec.Value.push_back(history10secValue);
    };

    /*
     * XPATH: /SAFplusTypes/decStatistic/history1min
     */
    std::vector<long> DecStatistic::getHistory1min()
    {
        return this->history1min.Value;
    };

    /*
     * XPATH: /SAFplusTypes/decStatistic/history1min
     */
    void DecStatistic::setHistory1min(long history1minValue)
    {
        this->history1min.Value.push_back(history1minValue);
    };

    /*
     * XPATH: /SAFplusTypes/decStatistic/history10min
     */
    std::vector<long> DecStatistic::getHistory10min()
    {
        return this->history10min.Value;
    };

    /*
     * XPATH: /SAFplusTypes/decStatistic/history10min
     */
    void DecStatistic::setHistory10min(long history10minValue)
    {
        this->history10min.Value.push_back(history10minValue);
    };

    /*
     * XPATH: /SAFplusTypes/decStatistic/history1hour
     */
    std::vector<long> DecStatistic::getHistory1hour()
    {
        return this->history1hour.Value;
    };

    /*
     * XPATH: /SAFplusTypes/decStatistic/history1hour
     */
    void DecStatistic::setHistory1hour(long history1hourValue)
    {
        this->history1hour.Value.push_back(history1hourValue);
    };

    /*
     * XPATH: /SAFplusTypes/decStatistic/history12hour
     */
    std::vector<long> DecStatistic::getHistory12hour()
    {
        return this->history12hour.Value;
    };

    /*
     * XPATH: /SAFplusTypes/decStatistic/history12hour
     */
    void DecStatistic::setHistory12hour(long history12hourValue)
    {
        this->history12hour.Value.push_back(history12hourValue);
    };

    /*
     * XPATH: /SAFplusTypes/decStatistic/history1day
     */
    std::vector<long> DecStatistic::getHistory1day()
    {
        return this->history1day.Value;
    };

    /*
     * XPATH: /SAFplusTypes/decStatistic/history1day
     */
    void DecStatistic::setHistory1day(long history1dayValue)
    {
        this->history1day.Value.push_back(history1dayValue);
    };

    /*
     * XPATH: /SAFplusTypes/decStatistic/history1week
     */
    std::vector<long> DecStatistic::getHistory1week()
    {
        return this->history1week.Value;
    };

    /*
     * XPATH: /SAFplusTypes/decStatistic/history1week
     */
    void DecStatistic::setHistory1week(long history1weekValue)
    {
        this->history1week.Value.push_back(history1weekValue);
    };

    /*
     * XPATH: /SAFplusTypes/decStatistic/history1month
     */
    std::vector<long> DecStatistic::getHistory1month()
    {
        return this->history1month.Value;
    };

    /*
     * XPATH: /SAFplusTypes/decStatistic/history1month
     */
    void DecStatistic::setHistory1month(long history1monthValue)
    {
        this->history1month.Value.push_back(history1monthValue);
    };

    DecStatistic::~DecStatistic()
    {
    };

}
/* namespace SAFplusTypes */
