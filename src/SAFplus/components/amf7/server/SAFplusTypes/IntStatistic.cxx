/* 
 * File IntStatistic.cxx
 * This file has been auto-generated by Y2CPP, the
 * plug-in of pyang.
 */ 
#include "SAFplusTypesCommon.hxx"

#include "clMgtObject.hxx"
#include "clMgtProv.hxx"
#include <vector>
#include "MgtFactory.hxx"
#include "clMgtProvList.hxx"
#include "IntStatistic.hxx"


namespace SAFplusTypes
  {

    /* Apply MGT object factory */
    REGISTERIMPL(IntStatistic, /intStatistic)

    IntStatistic::IntStatistic(): ClMgtObject("intStatistic"), current("current"), history10sec("history10sec"), history1min("history1min"), history10min("history10min"), history1hour("history1hour"), history12hour("history12hour"), history1day("history1day"), history1week("history1week"), history1month("history1month")
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

    std::vector<std::string>* IntStatistic::getChildNames()
    {
        std::string childNames[] = { "current", "history10sec", "history1min", "history10min", "history1hour", "history12hour", "history1day", "history1week", "history1month" };
        return new std::vector<std::string> (childNames, childNames + sizeof(childNames) / sizeof(childNames[0]));
    };

    /*
     * XPATH: /SAFplusTypes/intStatistic/current
     */
    unsigned long int IntStatistic::getCurrent()
    {
        return this->current.Value;
    };

    /*
     * XPATH: /SAFplusTypes/intStatistic/current
     */
    void IntStatistic::setCurrent(unsigned long int currentValue)
    {
        this->current.Value = currentValue;
    };

    /*
     * XPATH: /SAFplusTypes/intStatistic/history10sec
     */
    std::vector<unsigned long int> IntStatistic::getHistory10sec()
    {
        return this->history10sec.Value;
    };

    /*
     * XPATH: /SAFplusTypes/intStatistic/history10sec
     */
    void IntStatistic::setHistory10sec(unsigned long int history10secValue)
    {
        this->history10sec.Value.push_back(history10secValue);
    };

    /*
     * XPATH: /SAFplusTypes/intStatistic/history1min
     */
    std::vector<unsigned long int> IntStatistic::getHistory1min()
    {
        return this->history1min.Value;
    };

    /*
     * XPATH: /SAFplusTypes/intStatistic/history1min
     */
    void IntStatistic::setHistory1min(unsigned long int history1minValue)
    {
        this->history1min.Value.push_back(history1minValue);
    };

    /*
     * XPATH: /SAFplusTypes/intStatistic/history10min
     */
    std::vector<unsigned long int> IntStatistic::getHistory10min()
    {
        return this->history10min.Value;
    };

    /*
     * XPATH: /SAFplusTypes/intStatistic/history10min
     */
    void IntStatistic::setHistory10min(unsigned long int history10minValue)
    {
        this->history10min.Value.push_back(history10minValue);
    };

    /*
     * XPATH: /SAFplusTypes/intStatistic/history1hour
     */
    std::vector<unsigned long int> IntStatistic::getHistory1hour()
    {
        return this->history1hour.Value;
    };

    /*
     * XPATH: /SAFplusTypes/intStatistic/history1hour
     */
    void IntStatistic::setHistory1hour(unsigned long int history1hourValue)
    {
        this->history1hour.Value.push_back(history1hourValue);
    };

    /*
     * XPATH: /SAFplusTypes/intStatistic/history12hour
     */
    std::vector<unsigned long int> IntStatistic::getHistory12hour()
    {
        return this->history12hour.Value;
    };

    /*
     * XPATH: /SAFplusTypes/intStatistic/history12hour
     */
    void IntStatistic::setHistory12hour(unsigned long int history12hourValue)
    {
        this->history12hour.Value.push_back(history12hourValue);
    };

    /*
     * XPATH: /SAFplusTypes/intStatistic/history1day
     */
    std::vector<unsigned long int> IntStatistic::getHistory1day()
    {
        return this->history1day.Value;
    };

    /*
     * XPATH: /SAFplusTypes/intStatistic/history1day
     */
    void IntStatistic::setHistory1day(unsigned long int history1dayValue)
    {
        this->history1day.Value.push_back(history1dayValue);
    };

    /*
     * XPATH: /SAFplusTypes/intStatistic/history1week
     */
    std::vector<unsigned long int> IntStatistic::getHistory1week()
    {
        return this->history1week.Value;
    };

    /*
     * XPATH: /SAFplusTypes/intStatistic/history1week
     */
    void IntStatistic::setHistory1week(unsigned long int history1weekValue)
    {
        this->history1week.Value.push_back(history1weekValue);
    };

    /*
     * XPATH: /SAFplusTypes/intStatistic/history1month
     */
    std::vector<unsigned long int> IntStatistic::getHistory1month()
    {
        return this->history1month.Value;
    };

    /*
     * XPATH: /SAFplusTypes/intStatistic/history1month
     */
    void IntStatistic::setHistory1month(unsigned long int history1monthValue)
    {
        this->history1month.Value.push_back(history1monthValue);
    };

    IntStatistic::~IntStatistic()
    {
    };

}
/* namespace SAFplusTypes */
