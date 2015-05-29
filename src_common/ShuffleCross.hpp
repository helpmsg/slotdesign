#include "Game.hpp"
#include "Reel.hpp"

#ifndef SHUFFLECROSS_HPP
#define SHUFFLECROSS_HPP

class WinCalcShuffleCross : public WinCalculator
{
public:
	int leftWin(const Window& window, Window* highlight = NULL) const
	{
		int partialWin = 0;
		partialWin += this->crissCrossWin(window, highlight);
		return partialWin;
	}
};

class GameShuffleCross : public Game
{
	ReelSet reelSetMain;
	WinCalcShuffleCross winCalc;
	Payline paylines[Settings::paylineCount];

public:
	void load()
	{
		Input* rsMain = InputLoader::open(INPUT(res_reelset0));
		Input* ptable = InputLoader::open(INPUT(res_paytable));
		this->reelSetMain.load(rsMain);
		this->winCalc.loadPaytable(ptable);
		InputLoader::close(rsMain);
		InputLoader::close(ptable);
	}

	std::string getRSVersion() const
	{
		std::string result("0");
		return result;
	}

private:
	void updateStats()
	{
		int winBasic = this->winCalc.leftWin(this->window);
		this->lastWinAmount = winBasic;
		this->stats.statWin.addData(this->lastWinAmount);
		this->stats.statWinBasic.addData(winBasic);
		if (lastWinAmount == 0)
			this->stats.statWin0.addData();
		else if (lastWinAmount <= 100)
			this->stats.statWinU100.addData();
		else if (lastWinAmount <= 200)
			this->stats.statWinU200.addData();
		else
			this->stats.statWinO200.addData();
		if (this->lastWinAmount > this->stats.maxWin)
			this->stats.maxWin = this->lastWinAmount;
	}

	void spin()
	{
		this->reelSetMain.shuffleReels();
		this->reelSetMain.spin(&this->window);
	
		this->windowReady = true;
	}
};
#endif