void DrawPlots() {
	TDatabasePDG pdg;
	vector<TParticlePDG*> charmed_hadrons;
	
	// Set colours for different quarks 
	std::map<int, int> quarks {
		{1, kBlue+2}, 		//d
		{2, kGreen+2},		//u 
		{3, kMagenta+2},	//s 
		{4, kRed+2}, 		//c
		{-1, kBlue},  		//d_bar
		{-2, kGreen},   	//u_bar
		{-3, kMagenta},  	//s_bar
		{-4, kRed}  		//c_bar
	};
	
	// Set lifetimes of charm particles since they are zero in the ROOT PDG Database
	std::map<int, double> lifetimes {
		{-411, 1.033*1e-12},    //D-
		{411, 1.033*1e-12},     //D+	
		{421, 4.103*1e-13},     //D0
		{4122, 2.015*1e-13},    //Lambda_c+
		{4222, 3.500*1e-22},    //Sigma_c++ (using Gamma width of resonance)
		{4212, 1.400*1e-22},    //Sigma_c+ (using Gamma width of resonance)
		{4112, 3.600*1e-22},    //Sigma_c0 (using Gamma width of resonance)
		{4232, 4.530*1e-13},    //Xi_c+
		{4132, 1.519*1e-13},    //Xi_c0
		{4332, 2.680*1e-13},    //Omega_c0
	};
	
	// Initialize charm particles with PDG Database
	charmed_hadrons.push_back(pdg.GetParticle(-411));    //D-
	charmed_hadrons.push_back(pdg.GetParticle(411));     //D+	
	charmed_hadrons.push_back(pdg.GetParticle(421));     //D0
	charmed_hadrons.push_back(pdg.GetParticle(4122));    //Lambda_c+
	charmed_hadrons.push_back(pdg.GetParticle(4222));    //Sigma_c++
	charmed_hadrons.push_back(pdg.GetParticle(4212));    //Sigma_c+
	charmed_hadrons.push_back(pdg.GetParticle(4112));    //Sigma_c0
	charmed_hadrons.push_back(pdg.GetParticle(4232));    //Xi_c+
	charmed_hadrons.push_back(pdg.GetParticle(4132));    //Xi_c0
	charmed_hadrons.push_back(pdg.GetParticle(4332));    //Omega_c0
	
	// Create pies for each particle
	vector<TPie*> pies;
	for (auto particle:charmed_hadrons) {
		// Case of D- (meson, antiparticle)
		if (particle->PdgCode()/1000 == 0 && particle->Charge() < 0) {
			float parts[2] = {.5, .5};
			int colours[2] = {quarks.at(particle->PdgCode()/100), quarks.at(-1*particle->PdgCode()/10%10)};
			const char *labels[2] = {pdg.GetParticle(particle->PdgCode()/100)->GetName(), pdg.GetParticle(-1*particle->PdgCode()/10%10)->GetName()};
			pies.push_back(new TPie(Form("pie_%s", particle->GetName()), particle->GetName(), 2, parts, colours));
			pies.back()->SetLabels(labels);
//			pies.back()->SetRadius(TMath::Sqrt(particle->Lifetime()*(1e11)));
			pies.back()->SetRadius(TMath::Sqrt(lifetimes.at(particle->PdgCode())*(1e11)));
		}
		// Case of other mesons
		else if (particle->PdgCode()/1000 == 0 && particle->Charge() >= 0) {
			float parts[2] = {.5, .5};
			int colours[2] = {quarks.at(particle->PdgCode()/100), quarks.at(-1*particle->PdgCode()/10%10)};
			const char *labels[2] = {pdg.GetParticle(particle->PdgCode()/100)->GetName(), pdg.GetParticle(-1*particle->PdgCode()/10%10)->GetName()};
			pies.push_back(new TPie(Form("pie_%s", particle->GetName()), particle->GetName(), 2, parts, colours));
			pies.back()->SetLabels(labels);
//			pies.back()->SetRadius(TMath::Sqrt(particle->Lifetime()*(1e11)));
			pies.back()->SetRadius(TMath::Sqrt(lifetimes.at(particle->PdgCode())*(1e11)));
		}
		// Case of baryons
		else {
			float parts[3] = {1./3., 1./3., 1./3.};
			int colours[3] = {quarks.at(particle->PdgCode()/1000), quarks.at(particle->PdgCode()/100%10), quarks.at(particle->PdgCode()/10%10)};
			const char *labels[3] = {pdg.GetParticle(particle->PdgCode()/1000)->GetName(), pdg.GetParticle(particle->PdgCode()/100%10)->GetName(), pdg.GetParticle(particle->PdgCode()/10%10)->GetName()};
			pies.push_back(new TPie(Form("pie_%s", particle->GetName()), particle->GetName(), 3, parts, colours));
			pies.back()->SetLabels(labels);
//			pies.back()->SetRadius(TMath::Sqrt(particle->Lifetime()*(1e11)));
			pies.back()->SetRadius(TMath::Sqrt(lifetimes.at(particle->PdgCode())*(1e11)));
		}
	}
	
	// Draw pies on canvas
	TCanvas *plots = new TCanvas("plots", "Charmed particles", 2000, 700);
	plots->Divide(5, 2);
	for (int i=0; i<pies.size(); i++) {
		plots->cd(i+1);
		pies.at(i)->Draw("nol <");
	}
}
