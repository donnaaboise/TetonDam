PYTHON=python

EXE=vcatch

topo:
	echo "Not needed for the Teton Dam example"
	# ${PYTHON} maketopo.py  # Essentially maketopo.py

data:
	${PYTHON} setrun.py  # Essentially setrun.py

output:
	@echo "Usage : "
	@echo "    To run example in serial : "
	@echo "           $$ ${EXE}"
	@echo "     "
	@echo "    To run example in parallel : "
	@echo "           $$ mpirun -n 4 ${EXE}"
	@echo "     "

plots: 
	${PYTHON} setplot.py   # Essentially setplot.py

kml: 
	${PYTHON} setplot_kml.py     # Version of setplot.py for creating KML files.

usage:
	@echo "Usage : "
	@echo "To create data files needed by TetonDam example : "
	@echo "       $$ make data"
	@echo " "
	@echo "To produce output"
	@echo "       $$ make output"
	@echo " "
	@echo "To create plots using VisClaw"
	@echo "       $$ make plots"
	@echo " "
	@echo "To create KMZ file for plotting in Google Earth"
	@echo "       $$ make kml"
