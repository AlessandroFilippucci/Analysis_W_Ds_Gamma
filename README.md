# Feasibility Study: $W^+ \rightarrow D_s^+ \gamma \rightarrow K^+ K^- \pi^+ \gamma$

This repository contains the main project files for my Master's thesis in Physics at the University of Perugia.

The project consists of a feasibility study for the analysis of an extremely rare physical process that has never been observed before, but only theorized: 
the radiative hadronic decay $W^+ \rightarrow D_s^+ \gamma \rightarrow K^+ K^- \pi^+ \gamma$.

The code development was entirely based on the structural characteristics and capabilities of the CMS particle detector, installed at CERN's Large Hadron Collider (LHC) in Geneva.

## Project Workflow

* **Simulation:** Simulation of the physical process using the Pythia8 Monte Carlo simulation software, due to the lack of real experimental data caused by the rarity of the process.
* **Data Transformation:** Conversion of the simulated data into a format suitable for analysis, using tools provided by the CMS Collaboration. (Note: These tools are restricted and accessible only to collaboration members).
* **Data Analysis:** Analysis of the simulated data using a custom C++ code based on ROOT, a data analysis framework developed at CERN.
* **Visualization:** Creation of ROOT macros to visualize the analysis results (histograms).

## Repository Contents

Below is the list of files included in this repository, along with a brief description of each:

* **`Event_Generation.py`**: Python script used to generate simulated events via Pythia8.
* **`W+_to_Ds+_Gamma.cc`**: C++ macro for analyzing the simulated data and producing histograms.
* **`Istograms_Visualization.C`**: ROOT macro dedicated to visualizing the histograms generated during the analysis stage.

> [!NOTE]
> The configuration script for the data transformation step is not included here, as that process was carried out using proprietary tools specific to the CMS Collaboration.