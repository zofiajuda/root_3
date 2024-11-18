TGraph *Wykresy(double energia = 12., int color = 2, int marker = 8)
{
    const Int_t n = 91;
    TString nazwa = Form("pp0%.3fang.L01", energia);

    fstream dane(nazwa, ios::in); // otwarcie pliku tekstowego do odczytu
    if (!dane.is_open())
    { // sprawdzenie czy plik poprawnie otwarto
        cout << "Nie mozna otworzyc pliku tekstowego" << endl;
    }

    Double_t katy[n];
    Double_t pczynny[n];
    Double_t dummy;
    TString naglowek;
    for (Int_t i = 0; i < 5; i++)
    { // wczytanie nagłówka pliku
        naglowek.ReadLine(dane);
    }
    for (Int_t j = 0; j < n; j++)
    { // wczytanie danych liczbowych
        dane >> katy[j] >> pczynny[j] >> dummy >> dummy;
    }
    TGraph *graph = new TGraph(n, katy, pczynny); // stworzenie wykresu
    graph->SetMarkerStyle(marker);                // formatowanie wykresu
    graph->SetMarkerColor(color);
    graph->SetMarkerSize(1);
    graph->SetLineColor(color);
    graph->SetName(Form("angdist_%.0fMeV", energia));
    graph->SetTitle(Form("Angular distribution (%.1f MeV);kat [deg];przekroj czynny [a.u.]", energia));
    // graph->Draw("AP");   // rysowanie

    return graph;
}

void rysuj_wszystko(TString file_name = "wykresy.root")
{
    TFile *rootfile = new TFile(file_name, "RECREATE");
    double energie[4] = {12., 20., 40., 65.};
    TGraph *wykresy[4] = {nullptr};
    TCanvas *c = new TCanvas("c1", "c1", 1028, 1028);
    c->Divide(2, 2);

    TCanvas *c1 = new TCanvas("c11", "c11", 1028, 1028);
    TMultiGraph *mg = new TMultiGraph();
    TLegend *leg = new TLegend(0.588694, 0.533742, 0.901559, 0.675869, "Rozklady");
    for (int i = 0; i < 4; i++)
    {
        wykresy[i] = Wykresy(energie[i], 1 + i, 20 + i);
        mg->Add(wykresy[i], "AP");
        c->cd(i + 1);
        wykresy[i]->Draw("AP");
        gPad->SetGrid(1, 1); // siatka
        leg->AddEntry(wykresy[i], Form("Energia: %.3f", energie[i]));
        wykresy[i]->Write();
        // leg->Draw();
    }
    c1->cd();

    mg->Draw("AP");
    mg->SetTitle("Angular distribution for different energies;kat [deg];przekroj czynny [a.u.]");
    leg->Draw();
}