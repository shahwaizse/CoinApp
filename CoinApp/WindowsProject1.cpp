#pragma once
#include "wx/wx.h"
#include "wx/splash.h"
#include "wx/arrstr.h"
#include "wx/grid.h"
#include "wx/animate.h"
#include<fstream>
#include "sql_functions.h"

using namespace std;

class cMain : public wxFrame
{
public:
	wxButton* buybuttton = nullptr;
	wxTextCtrl* buyinput = nullptr;
	wxTextCtrl* sellinput = nullptr;
	wxTextCtrl* transferinput1 = nullptr;
	wxTextCtrl* transferinput2 = nullptr;
	wxTextCtrl* usernameinput = nullptr;
	wxTextCtrl* passwordinput = nullptr;
	wxTextCtrl* walletidinput = nullptr;
	wxListBox* m_list1 = nullptr;
	wxListBox* m_list2 = nullptr;
	wxButton* sellbuttton = nullptr;
	wxButton* refreshbuttton = nullptr;
	wxButton* transferbuttton = nullptr;
	wxButton* loginbuttton = nullptr;
	wxButton* registerbuttton = nullptr;
	wxChoice* m_choice1 = nullptr;
	wxChoice* m_choice2 = nullptr;
	wxChoice* m_choice3 = nullptr;
	wxStaticBitmap* t_prices = nullptr;
	wxStaticBitmap* t_wallet = nullptr;
	wxStaticBitmap* coinicon = nullptr;
	wxStaticBitmap* walleticon = nullptr;
	//wxStaticBitmap* sideicon = nullptr;
	wxStaticText* text1 = nullptr;
	wxStaticText* text2 = nullptr;
	wxStaticText* text3 = nullptr;
	wxAnimationCtrl* m_rotate = nullptr;

	cMain() : wxFrame(nullptr, wxID_ANY, "AltCoin", wxDefaultPosition, wxSize(1100, 600)) {
		SetBackgroundColour(wxColor(0, 22, 145));
		buybuttton = new wxButton(this, 1, "Buy Coin", wxPoint(530, 70), wxSize(180, 60));
		sellbuttton = new wxButton(this, 2, "Sell Coin", wxPoint(830, 70), wxSize(180, 60));
		refreshbuttton = new wxButton(this, 3, "Refresh Prices", wxPoint(180, 30), wxSize(90, 30));
		transferbuttton = new wxButton(this, 4, "Transfer Amount", wxPoint(530, 250), wxSize(180, 60));
		loginbuttton = new wxButton(this, 5, "Login", wxPoint(860, 480), wxSize(90, 25));
		registerbuttton = new wxButton(this, 6, "Register", wxPoint(860, 510), wxSize(90, 25));
		buyinput = new wxTextCtrl(this, wxID_ANY, "", wxPoint(640, 140), wxSize(70, 25));
		sellinput = new wxTextCtrl(this, wxID_ANY, "", wxPoint(940, 140), wxSize(70, 25));
		transferinput1 = new wxTextCtrl(this, wxID_ANY, "", wxPoint(640, 320), wxSize(70, 25));
		transferinput2 = new wxTextCtrl(this, wxID_ANY, "", wxPoint(530, 355), wxSize(180, 25));
		usernameinput = new wxTextCtrl(this, wxID_ANY, "", wxPoint(550, 480), wxSize(280, 25));
		passwordinput = new wxTextCtrl(this, wxID_ANY, "", wxPoint(550, 510), wxSize(280, 25));
		walletidinput = new wxTextCtrl(this, wxID_ANY, "", wxPoint(970, 10), wxSize(100, 25));
		m_list1 = new wxListBox(this, wxID_ANY, wxPoint(20, 70), wxSize(400, 200));
		m_list2 = new wxListBox(this, wxID_ANY, wxPoint(20, 330), wxSize(400, 200));
		text1 = new wxStaticText(this, wxID_ANY, "USERNAME", wxPoint(480, 480), wxSize(60, 20), wxALIGN_LEFT);
		text1->SetForegroundColour(wxColor(*wxWHITE));
		text2 = new wxStaticText(this, wxID_ANY, "PASSWORD", wxPoint(480, 510), wxSize(60, 20), wxALIGN_LEFT);
		text2->SetForegroundColour(wxColor(*wxWHITE));
		text3 = new wxStaticText(this, wxID_ANY, "WALLET_ID", wxPoint(900, 15), wxSize(60, 20), wxALIGN_LEFT);
		text3->SetForegroundColour(wxColor(*wxWHITE));
		wxArrayString coin;
		coin.Add("BTCUSDT");
		coin.Add("ETHUSDT");
		coin.Add("SOLUSDT");
		coin.Add("LUNAUSDT");
		coin.Add("LUNCBUSDT");
		coin.Add("SHIBUSDT");
		coin.Add("ADAUSDT");
		coin.Add("APEUSDT");
		coin.Add("DOGEUSDT");
		coin.Add("DOTUSDT");
		wxArrayString transferamount;
		transferamount.Add("ID Below");
		m_choice1 = new wxChoice(this, wxID_ANY, wxPoint(530, 140), wxSize(100, 60), coin);
		m_choice1->SetSelection(0);
		m_choice2 = new wxChoice(this, wxID_ANY, wxPoint(830, 140), wxSize(100, 60), coin);
		m_choice2->SetSelection(0);
		m_choice3 = new wxChoice(this, wxID_ANY, wxPoint(530, 320), wxSize(100, 60), transferamount);
		m_choice3->SetSelection(0);
		wxPNGHandler* handler = new wxPNGHandler;
		wxImage::AddHandler(handler);
		t_prices = new wxStaticBitmap(this, wxID_ANY, wxBitmap("C:/Users/mshah/Downloads/prices.png",
			wxBITMAP_TYPE_PNG), wxPoint(20, 30), wxSize(100, 40));
		t_wallet = new wxStaticBitmap(this, wxID_ANY, wxBitmap("C:/Users/mshah/Downloads/wallet.png",
			wxBITMAP_TYPE_PNG), wxPoint(20, 290), wxSize(100, 40));
		coinicon = new wxStaticBitmap(this, wxID_ANY, wxBitmap("C:/Users/mshah/Downloads/coinicon.png",
			wxBITMAP_TYPE_PNG), wxPoint(115, 25), wxSize(40, 40));
		walleticon = new wxStaticBitmap(this, wxID_ANY, wxBitmap("C:/Users/mshah/Downloads/walleticon.png",
			wxBITMAP_TYPE_PNG), wxPoint(115, 285), wxSize(40, 40));
		/*sideicon = new wxStaticBitmap(this, wxID_ANY, wxBitmap("C:/Users/mshah/Downloads/sideicon.png",
			wxBITMAP_TYPE_PNG), wxPoint(1000, 470), wxSize(200, 200));*/
		m_rotate = new wxAnimationCtrl(this, wxID_ANY, wxNullAnimation, wxPoint(800, 230));
		if (m_rotate->LoadFile(wxT("C:/Users/mshah/OneDrive/Pictures/coin.gif")))
			m_rotate->Play();
		refreshpricestartup();
		//refreshwalletstartup();
	}
	~cMain() {}
	void refreshprice(wxCommandEvent& evt) {
		/*string filename = "C:/Users/mshah/OneDrive/Desktop/meh/scrape.pyw"; //file named .pyw to supress window popup
		string command = "";
		command += filename;
		system(command.c_str());
		Sleep(5);*/

		refreshpricestartup();
		fstream file;
		string s;
		file.open("C:/Users/mshah/OneDrive/Desktop/scrape_script/infodump.txt", ios::in);
		int counter = 0;
		string arr[3];
		float prc; float rt; string id;
		//getline(file, s) this is for below while loop parameter
		while (1) {
			file >> s;
			if (file.eof()) {
				break;
			}
			arr[counter] = s;
			counter++;
			if (counter == 3) {
				prc = stof(arr[1]);
				rt = stof(arr[2]);
				updateprice(prc, rt, arr[0]);
				counter = 0;
			}
		}
		file.close();
		evt.Skip();
	}
	void refreshwalletstartup() {
		wxString temp = walletidinput->GetValue();
		string tempamount = string(temp.mb_str());
		int w_id = stoi(tempamount);
		walletdata w3 = displaywallet(w_id);
		m_list2->Clear();
		for (int i = 0; i < w3.coin_id.size(); i++) {
			m_list2->Append(w3.coin_id.at(i));
			int x = w3.amount.at(i);
			string str = to_string(x);
			m_list2->Append(str);
			m_list2->Append("");
		}
		//for (int i = 0; i < w3.amount.size(); i++) {}
	}
	void refreshpricestartup() {
		/*string filename = "C:/Users/mshah/OneDrive/Desktop/meh/scrape.pyw"; //file named .pyw to supress window popup
		string command = "";
		command += filename;
		system(command.c_str());
		Sleep(5);*/

		m_list1->Clear();
		fstream file;
		string s;
		file.open("C:/Users/mshah/OneDrive/Desktopscrape_script/infodump.txt", ios::in);
		while (getline(file, s)) {
			m_list1->AppendString(s);
		}
		file.close();
	}
	
	//transaction functions.
	
	void buy(wxCommandEvent& evt) {
		//m_list1->AppendString(buyinput->GetValue()); this was for testing and is unrelated.
		
		wxString temp0 = m_choice1->GetString(m_choice1->GetSelection());
		string coinid = string(temp0.mb_str());
		wxString temp = buyinput->GetValue();
		string tempamount = string(temp.mb_str());
		int amount = stoi(tempamount);
		wxString temp2 = walletidinput->GetValue();
		string tempwid = string(temp2.mb_str());
		int wid = stoi(tempwid);

		buycoin(coinid, amount, wid);
		refreshwalletstartup();

		//wxMessageBox("added to list");
		evt.Skip();
	}
	void sell(wxCommandEvent& evt) {

		wxString temp0 = m_choice2->GetString(m_choice2->GetSelection());
		string coinid = string(temp0.mb_str());
		wxString temp = sellinput->GetValue();
		string tempamount = string(temp.mb_str());
		int amount = stoi(tempamount);
		wxString temp2 = walletidinput->GetValue();
		string tempwid = string(temp2.mb_str());
		int wid = stoi(tempwid);

		sellcoin(coinid, amount, wid);
		refreshwalletstartup();

		evt.Skip();
	}
	void transfer(wxCommandEvent& evt) {
		wxString amountstring = transferinput1->GetValue();
		string tempamount = string(amountstring.mb_str());
		int amount = stoi(tempamount);
		
		wxString recieverstring = walletidinput->GetValue();
		string recv = string(recieverstring.mb_str());
		int recieverid = stoi(recv);

		wxString senderstring = transferinput2->GetValue();
		string send = string(senderstring.mb_str());
		int senderid = stoi(send);

		transfercoin(recieverid, senderid, amount);
		refreshwalletstartup();

		evt.Skip();
	}

	void rgstr(wxCommandEvent& evt) {
		wxString usrnm = usernameinput->GetValue();
		wxString pswd = passwordinput->GetValue();
		string username = string(usrnm.mb_str());
		string password = string(pswd.mb_str());
		int wid = registeruser(username, password);
		if (wid == 0) {
			wxMessageBox("Error: Credentials already exist.");
			
			evt.Skip();
			return;
		}
		string swid = to_string(wid);
		wxMessageBox("Successfully registered.");
		//walletidinput->SetValue(swid);
		usernameinput->Clear();
		passwordinput->Clear();

		evt.Skip();
	}

	void login(wxCommandEvent& evt) {
		wxString usrnm = usernameinput->GetValue();
		wxString pswd = passwordinput->GetValue();
		string username = string(usrnm.mb_str());
		string password = string(pswd.mb_str());
		int wid  = loginuser(username, password);
		if (wid == 0) {
			wxMessageBox("Incorrect Credentials.");
			walletidinput->Clear();
			evt.Skip();
			return;
		}
		string swid = to_string(wid);
		wxMessageBox("Login successful.");
		walletidinput->SetValue(swid);
		evt.Skip();
	}

	//end of transaction functions.

	void addlist(wxCommandEvent& evt) {
		m_list1->AppendString(m_choice1->GetString(m_choice1->GetSelection()));
	}
	void clear(wxCommandEvent& evt) {
		m_list1->Clear();
	}
	wxDECLARE_EVENT_TABLE();
};
class cApp : public wxApp {
public:
	cApp() {}
	~cApp() {}
	bool OnInit() {
		wxInitAllImageHandlers();
		wxBitmap doge;
		if (doge.LoadFile("C:/Users/mshah/Downloads/doge.png", wxBITMAP_TYPE_PNG)) {
			wxSplashScreen* splash = new wxSplashScreen(doge, wxSPLASH_CENTRE_ON_SCREEN | wxSPLASH_TIMEOUT,
				1000, NULL, -1, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE | wxSTAY_ON_TOP);
		}
		wxYield();
		Sleep(2000);
		m_frame1 = new cMain();
		m_frame1->Show();
		return true;
	}
private:
	cMain* m_frame1 = nullptr;
};
wxIMPLEMENT_APP(cApp);

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
EVT_BUTTON(1, buy)
EVT_BUTTON(2, sell)
EVT_BUTTON(3, refreshprice)
EVT_BUTTON(4, transfer)
EVT_BUTTON(5, login)
EVT_BUTTON(6, rgstr)
wxEND_EVENT_TABLE()