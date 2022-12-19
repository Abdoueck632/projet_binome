/* run this program using the console pauser or add your own getch, system("pause") or input loop */
#include <iostream>
#include <string>
#include<fstream>
using namespace std;
int  tab_cout_emission[6]={560, 12, 11, 27, 24, 230};
//Enregistrement date (sous enregistrement)

struct Date {
    int mois;
    int jour;
    int heure;

};
// Enregistrement energie france
struct energie_france{
    int code_region;
    char* region;
    Date horodatage;
    int production_thermique;
    int production_nucleaire;
    int productin_eolienne;
    int production_solaire;
    int production_hydraulique;
    int production_bioenergies;
    float soldes_des_flux_sortants_et_entrants;
    float cout_maximum_moyen;

};
//Enregistrement cout moyen
struct cout_emissions{
    int production_thermique;
    int production_nucleaire;
    int productin_eolienne;
    int production_solaire;
    int production_hydraulique;
    int production_bioenergies;
};
// Enregistrement planification
struct planification{
    int region;
    int premier_heure;
    int dernier_heure;
    int couts;
};
struct Objectif{
    char nom_tache[20];
    char nom_fichier_result[25];
    int duree_tache;
    Date horodatage_debut;
    Date horodatage_fin;
    float cout_maximum;
    int* regions;



};
cout_emissions extract_couts_moyen() {

    ifstream f("couts_emissions.txt" );

    cout_emissions  cout_emission{};
    f >> cout_emission.production_thermique;
    f >> cout_emission.production_nucleaire;
    f >> cout_emission.productin_eolienne;
    f >> cout_emission.production_solaire;
    f >> cout_emission.production_hydraulique;
    f >> cout_emission.production_bioenergies;

    return cout_emission;


}
// extract tache
Objectif extract_tache(char* file_name){
    ifstream f(file_name);

    Objectif  tache{};

    f.getline(tache.nom_tache, 15);
    f.getline(tache.nom_fichier_result, 21);

    f >> tache.duree_tache;
    printf("%d ", tache.duree_tache);
    f >> tache.horodatage_debut.mois;
    f >> tache.horodatage_debut.jour;
    f >> tache.horodatage_debut.heure;
    f >> tache.horodatage_fin.mois;
    f >> tache.horodatage_fin.jour;
    f >> tache.horodatage_fin.heure;
    f >> tache.cout_maximum;
    int i=0;
    while(f){
        f >> tache.regions[i];
        i++;
    }
    return tache;



}
energie_france* extraction_donnees(char* file_name,int nbreElement){
    energie_france  tabE[nbreElement];

    ifstream f(file_name);
    for (size_t i = 0; i < nbreElement; i++)
    {
        f >> tabE[i].code_region;
        f >> tabE[i].horodatage.heure;
        f >> tabE[i].horodatage.jour;
        f >> tabE[i].horodatage.mois;
        f >> tabE[i].production_thermique;
        f >> tabE[i].production_nucleaire;
        f >> tabE[i].productin_eolienne;
        f >> tabE[i].production_solaire;
        f >> tabE[i].production_hydraulique;
        f >> tabE[i].production_bioenergies;
        f >> tabE[i].soldes_des_flux_sortants_et_entrants;

    }
    cout << tabE[105119].soldes_des_flux_sortants_et_entrants << endl;
    return tabE;

}
energie_france* cout_moyenne(energie_france* tabE){
    int taiille= sizeof(tabE) / sizeof(energie_france);
    cout_emissions coutEmission=extract_couts_moyen();
    for (int i = 0; i < 105120 ; ++i) {
        tabE[i].cout_maximum_moyen=(
           tabE[i].production_thermique*tab_cout_emission[0] +
           tabE[i].production_nucleaire*tab_cout_emission[1] +
           tabE[i].productin_eolienne*tab_cout_emission[2] +
           tabE[i].production_solaire*tab_cout_emission[3] +
           tabE[i].production_hydraulique*tab_cout_emission[4] +
           tabE[i].production_bioenergies*tab_cout_emission[5] ) /
                   (coutEmission.production_thermique +
                    coutEmission.production_nucleaire +
                    coutEmission.productin_eolienne +
                    coutEmission.production_solaire +
                    coutEmission.production_hydraulique +
                    coutEmission.production_bioenergies
   );
    }
    return tabE;
}
int main(int argc, char** argv){
    energie_france* tabE=extraction_donnees((char *)"energieFrance2021.txt",105120);
    cout << "Bienvenue Ngone !" << endl;
    tabE= cout_moyenne(tabE);
    cout << tabE[3].cout_maximum_moyen << endl;
    cout << extract_couts_moyen().production_thermique << endl;
    cout << extract_tache((char *)"tache1.txt").horodatage_fin.mois  << endl;
    return 0;
}