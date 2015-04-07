#ifndef STATISTICS_HPP
#define STATISTICS_HPP

// Averaging (and more statistical stuff) of one value
class StatItem
{
	long data;
	long count;
public:
	void addData(int d)
	{
		this->data += d;
		this->count++;
	}
	double getAvg() const
	{
		return double(this->data)/double(this->count);
	}
	double getPct(long base) const
	{
		return 100.0 * double(this->data)/double(base);
	}
	long getTotal() const
	{
		return this->data;
	}
};

// StatItem that stores all values, for example to compute variance afterwards
class StatItemStore : StatItem
{
	int* allData;
	int dataCount;
};

// Contains all global statistics from the simulation
// Evolution of stats after individual spis (to be graphed) will be written to file immediately
struct Statistics
{
	StatItem statWin;
	StatItem statSymbols[Settings::symbolCount];
	// ...more statistical idicators...
	void writeToFile() const
	{
	}
};

#endif