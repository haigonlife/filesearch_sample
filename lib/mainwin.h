#ifndef MAINWIN_H
#define MAINWIN_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QListWidget>
#include <QRadioButton>
#include <QStringList>
#include <QStringListModel>
#include <QCompleter>
#include <QLabel>
#include <map>
#include <string>
#include <unordered_map>
#include "viewwin.h"
#include "webpage.h"
#include "smartset.h"
#include "advertiser.h"

struct PRComp
{
  bool operator()(WebPage* lhs, WebPage* rhs){
    return (lhs->get_pr()) > (rhs->get_pr());
  }
};

struct AlphComp
{
  bool operator()(WebPage* lhs, WebPage* rhs){
    return (lhs->filename()) < (rhs->filename());
  }
};

//FUNCTORS FOR ADVERTISER CLASS
struct NameComp{
	bool operator()(Advertiser* lhs, Advertiser* rhs){
		return (lhs->getName() < rhs->getName());
	}
};

struct BidComp{
	bool operator()(Advertiser* lhs, Advertiser* rhs){
		return (lhs->getHighestBid() > rhs->getHighestBid());
	}
};

class MainWin : public  QWidget // you can also try QMainWindow
{
	Q_OBJECT

	public:
        MainWin(char* ifname, char* advert_input, char* advert_output);
		string input_name;
		~MainWin();
		void rank_pages(SmartSet<WebPage*>& s);

	protected:
		std::map<std::string, WebPage*> filename_to_page;
		std::map<std::string, SmartSet<WebPage*> > input_to_results;

	private slots:
		void searchClicked();
		void showAbout();
		void itemClicked(QListWidgetItem*);
		void adClicked(QListWidgetItem*);

	private:
		QPushButton* aboutButton;
		QPushButton* searchButton;
		QPushButton* quitButton;
		QLineEdit* queryText;
		QListWidget* list;
		QListWidget* ad_list;
		QRadioButton* alpha_radio_btn;
		QRadioButton* pr_radio_btn;
		QLabel* ad_label;
		QStringList wordList;
		QStringListModel* model;
		QCompleter* completer;

		//store other window
		ViewWin* view;

		//store advertisers
		vector<Advertiser*> advertisers_vec;
		unordered_map<string, Advertiser*> advertisers;
		void parseAdvertisers(char*);
		void search_advertisers(vector<Advertiser*>&, string);
		char* ad_output;
		void printBill();

		//store set of visited pages
		set<WebPage*> visited_pages;
};

#endif
