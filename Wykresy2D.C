void Wykresy2D()
{
    const Int_t n = 4;
    int npoints = 91;
    TGraph2D *graph = new TGraph2D(npoints * n); // stworzenie wykresu
    double energie[4] = {12., 20., 40., 65.};
    int it_point = 0;
    for (int i = 0; i < n; i++)
    {
        TString nazwa = Form("pp0%.3fang.L01", energie[i]);
        fstream dane(nazwa, ios::in); // otwarcie pliku tekstowego do odczytu
        if (!dane.is_open())
        { // sprawdzenie czy plik poprawnie otwarto
            cout << "Nie mozna otworzyc pliku tekstowego" << endl;
        }
        else
        {
            Double_t katy[npoints];
            Double_t pczynny[npoints];
            Double_t dummy;
            TString naglowek;
            for (Int_t ii = 0; ii < 5; ii++)
            { // wczytanie nagłówka pliku
                naglowek.ReadLine(dane);
            }
            for (Int_t j = 0; j < npoints; j++)
            { // wczytanie danych liczbowych
                dane >> katy[j] >> pczynny[j] >> dummy >> dummy;
                // cout << energie[i] << "\t" << katy[j] << "\t" << pczynny[j] << endl;
                graph->SetPoint(it_point, energie[i], katy[j], pczynny[j]);
                it_point++;
            }

            // graph->SetMarkerStyle(20 + i); // formatowanie wykresu
            // graph->SetMarkerColor(1 + i);
            // graph->SetMarkerSize(1);
            // graph->SetLineColor(1 + i);
            graph->SetTitle("Angular distribution for different energies;energy [MeV];kat [deg];przekroj czynny [a.u.]");
            // graph->SetName(Form("angdist_%.0fMeV", energia));
            // graph->SetTitle(Form("Angular distribution (%.1f MeV);kat [deg];przekroj czynny [a.u.]", energia));
            graph->Draw("lego2"); // rysowanie
            gPad->SetGrid(1, 1);  // siatka
        }
    }
}
// void rysuj_wszystko(TString file_name = "wykresy.root")
// {
//     TFile *rootfile = new TFile(file_name, "RECREATE");
//     double energie[4] = {12., 20., 40., 65.};
//     TGraph *wykresy[4] = {nullptr};
//     TCanvas *c = new TCanvas("c1", "c1", 1028, 1028);
//     c->Divide(2, 2);

//     TCanvas *c1 = new TCanvas("c11", "c11", 1028, 1028);
//     TMultiGraph *mg = new TMultiGraph();
//     TLegend *leg = new TLegend(0.588694, 0.533742, 0.901559, 0.675869, "Rozklady");
//     for (int i = 0; i < 4; i++)
//     {
//         wykresy[i] = Wykresy(energie[i], 1 + i, 20 + i);
//         mg->Add(wykresy[i], "AP");
//         c->cd(i + 1);
//         wykresy[i]->Draw("AP");
//         gPad->SetGrid(1, 1); // siatka
//         leg->AddEntry(wykresy[i], Form("Energia: %.3f", energie[i]));
//         wykresy[i]->Write();
//         // leg->Draw();
//     }
//     c1->cd();
//     c1->Write();
//     c->Write();
//     mg->Draw("AP");
//     mg->SetTitle("Angular distribution for different energies;kat [deg];przekroj czynny [a.u.]");
//     leg->Draw();
// }