#include"MeshBuilder.h"

/*----------------------------*/
/*Mesh Builder functions*/
/*----------------------------*/

void MeshBuilder::split_segment(double start, double end, Fragmentation_info fragmentation_info, vector<double>& splitted_segment)
{
	double Sn = end - start;
	double coeff = fragmentation_info.coeff;
	int N = fragmentation_info.n;
	double h;

	/*first step calculation*/
	if(coeff == 1.)
	{
		h = Sn / N;
	}
	else
	{
		h = Sn * (1 - coeff) / (1 - powl(coeff, N));
	}

	/*partitioning*/
	splitted_segment.clear();
	splitted_segment.resize(N + 1);
	splitted_segment[0] = start;
	//thickening to the beginning of the interval
	if(fragmentation_info.sign > 0)
	{
		for(int i = 1; i < N + 1; i++)
		{
			splitted_segment[i] = splitted_segment[i - 1] + h * powl(coeff, i - 1);
		}
	}
	//thickening to the ending of the interval
	else
	{
		for(int i = 1; i < N + 1; i++)
		{
			splitted_segment[i] = splitted_segment[i - 1] + h * powl(coeff, N - i);
		}
	}
	splitted_segment[N] = end;
}

int MeshBuilder::is_anomaly(int n_layer, Point2D midpoint)
{
	int n_anomaly = -1;
	bool found = false;
	for(int i = 0; i < n_anomalies && !found; i++)
	{
		if(n_layer == anomalies[i].n_layer)
		{
			n_anomaly = i;
			found = true;
		}
	}
	if(found)
	{
		if(midpoint[0] >= anomalies[n_anomaly].x0 && midpoint[0] <= anomalies[n_anomaly].xn &&
			midpoint[1] >= anomalies[n_anomaly].y0 && midpoint[1] <= anomalies[n_anomaly].yn)
		{
			return n_anomaly;
		}
		else
		{
			return -1;
		}
	}
	else
	{
		return -1;
	}

}

void MeshBuilder::print_layers()
{
	cout << "number of layers: " << n_layers << endl;
	for(int i = 0; i < layer_boundary_spl.size(); i++)
	{
		cout << "#boundary " << i << endl;
		layer_boundary_spl[i].display();
	}
		
}

void MeshBuilder::print_anomalies()
{
	cout << "number of anomalies: " << n_anomalies << endl;
	for(int i = 0; i < n_anomalies; i++)
	{
		cout << "#anomaly " << i << endl;
		anomalies[i].display();
	}
		
}

void MeshBuilder::print_fragmentation_info()
{
	cout << "X:" << endl;
	for(int i = 0; i < X_fragments.size(); i++)
	{
		X_fragments[i].display();
	}
	cout << "Y:" << endl;
	for(int i = 0; i < Y_fragments.size(); i++)
	{
		Y_fragments[i].display();
	}
	cout << "Z:" << endl;
	for(int i = 0; i < Z_fragments.size(); i++)
	{
		Z_fragments[i].display();
	}
	cout << endl;
}

void MeshBuilder::build_mesh()
{
	/*number of nodes along the axis*/
	int n_x;
	int n_y;
	int n_z;

	/*print all received data*/
	//print_layers();
	//print_anomalies();
	//print_fragmentation_info();
	//display_stlset(X_primitive);
	//display_stlset(Y_primitive);

	/*split all x/y - segments*/
	vector<double> splitted_segment;
	int k = 0;	//index for X_fragments vector
	for(auto iter = X_primitive.begin(); iter != prev(X_primitive.end()); iter++, k++)
	{
		auto iter2 = next(iter);
		split_segment(*iter, *iter2, X_fragments[k], splitted_segment);

		for(int i = 0; i < splitted_segment.size() - 1; i++)
		{
			X_splitted.push_back(splitted_segment[i]);
		}
	}
	//add last element
	X_splitted.push_back(splitted_segment[splitted_segment.size()-1]);

	k = 0;	//index for Y_fragments vector
	for(auto iter = Y_primitive.begin(); iter != prev(Y_primitive.end()); iter++, k++)
	{
		auto iter2 = next(iter);
		split_segment(*iter, *iter2, Y_fragments[k], splitted_segment);

		for(int i = 0; i < splitted_segment.size() - 1; i++)
		{
			Y_splitted.push_back(splitted_segment[i]);
		}
	}
	//add last element
	Y_splitted.push_back(splitted_segment[splitted_segment.size() - 1]);
	
	//display_stlvector(X_splitted);
	//display_stlvector(Y_splitted);

	n_x = int(X_splitted.size());
	n_y = int(Y_splitted.size());
	n_z = 0;
	for(int i = 0; i < Z_fragments.size(); i++)
	{
		n_z += Z_fragments[i].n;
	}
	n_z += 1;


	k = 0;	//index for z-segments
	/*LAYERS LOOP*/
	for(int i_layer = 0; i_layer < n_layers; i_layer++)
	{
		/*make z - splitting*/
		split_segment(0, 1, Z_fragments[i_layer], splitted_segment);
		//display_stlvector(splitted_segment);

		int i_z = 0; 
		//skip first value cause it was processed in previous iteration
		if(i_layer != 0)
			i_z = 1;
		/*Z - SPLITTED LOOP*/
		for(; i_z < splitted_segment.size(); i_z++)
		{
			/*Y - SPLITTED LOOP*/
			for(int i_y = 0; i_y < Y_splitted.size(); i_y++)
			{
				/*X - SPLITTED LOOP*/
				for(int i_x = 0; i_x < X_splitted.size(); i_x++)
				{
					/*----------------------------*/
					/*NODE COORDINATES CALCULATION*/
					/*----------------------------*/
					/*z-value in i_layer layer*/
					double z0;
					/*z-value in i_layer + 1 layer*/
					double z1;
					/*current z-value*/
					double z;

					z0 = layer_boundary_spl[i_layer].get_value(X_splitted[i_x], Y_splitted[i_y]);
					z1 = layer_boundary_spl[i_layer + 1].get_value(X_splitted[i_x], Y_splitted[i_y]);
					z = z0 + (z1 - z0)*splitted_segment[i_z];

					nodes.push_back(Node3D(X_splitted[i_x], Y_splitted[i_y], z, int(nodes.size()), true));

					/*----------------------------*/
					/*FIRST BC CALCULATION        */
					/*----------------------------*/
					if(i_z == 0)
					{
						firstBCs.push_back(FirstBC(int(nodes.size() - 1), 0));
					}

					/*----------------------------*/
					/*FINITE ELEMENTS CALCULATION */
					/*----------------------------*/

					/*skip last iteration along the x and y axis*/
					/*skip first iteration along the z axis in first layer*/
					if(i_x == n_x - 1 || i_y == n_y - 1 || i_z == 0)
						continue;

					int shift1 = i_y * n_x;	//level up y
					int shift2 = n_x * n_y;	//level up z

					int lowlleft = i_x + shift1 + shift2 * k;
					int lowlright = i_x + shift1 + shift2 * k + 1;
					int lowuleft = i_x + shift1 + shift2 * k + n_x;
					int lowuright = i_x + shift1 + shift2 * k + n_x + 1;

					int uplleft = lowlleft + shift2;
					int uplright = lowlright + shift2;
					int upuleft = lowuleft + shift2;
					int upuright = lowuright + shift2;

					double x_mid;
					double y_mid;

					x_mid = X_splitted[i_x] + (X_splitted[i_x + 1] - X_splitted[i_x]) / 2.;
					y_mid = Y_splitted[i_y] + (Y_splitted[i_y + 1] - Y_splitted[i_y]) / 2.;

					int n_formula;
					/*check the fe belonging to the anomaly area*/
					int n_anomaly = is_anomaly(i_layer, Point2D(x_mid, y_mid));
					if(n_anomaly != -1)
					{
						/*get number for current anomaly*/
						n_formula = formula_anomaly[n_anomaly];
					}
					else
					{
						/*get number for current layer*/
						n_formula = formula_layer[i_layer];
					}

					vector<int> numbers = {lowlleft, lowlright, lowuleft, lowuright, uplleft, uplright, upuleft, upuright};
					fes.push_back(FE(numbers, n_formula, true));
				}
				/*X - SPLITTED LOOP*/
			}
			/*Y - SPLITTED LOOP*/

			if(!n_layers == 0 && !i_z == 0)
				k++;
		}
		/*Z - SPLITTED LOOP*/
	}
	/*LAYERS LOOP*/
	n_nodes = int(nodes.size());
	n_fes = int(fes.size());
	n_firstBCs = int(firstBCs.size());
}

void MeshBuilder::set_layer_boundary()
{
	set_layer_boundary(default_file_enviroment);
}

void MeshBuilder::set_layer_boundary(const char * file_name)
{
	string line;		//line read from file
	string num;			//string containing one number
	stringstream nums;	//string containing all numbers from line
	ifstream in;
	in.open(file_name, ifstream::in);

	vector<double> X;
	vector<double> Y;
	Matrix Z;

	if(in.is_open())
	{
		/*read number of layers*/
		std::getline(in, num);

		while(num == "")	//skip empty lines
			std::getline(in, num);
		string_to_number(num, n_layers);

		/*read layer boundary coordinates*/
		for(int i = 0; i < n_layers + 1; i++)
		{
			//read x-coordinates
			std::getline(in, line);
			while(line == "")	//skip empty lines
				std::getline(in, line);
			nums.str(line);
			while(nums >> num)
			{
				double x;
				string_to_number(num, x);
				X.push_back(x);
			}
			nums.clear();
			nums.str(string());

			//read y-coordinates
			std::getline(in, line);
			while(line == "")	//skip empty lines
				std::getline(in, line);
			nums.str(line);
			while(nums >> num)
			{
				double y;
				string_to_number(num, y);
				Y.push_back(y);
			}
			nums.clear();
			nums.str(string());

			Z = Matrix(int(Y.size()), int(X.size()));

			//read z-values
			for(int k = 0; k < Y.size(); k++)
			{
				std::getline(in, line);
				while(line == "")	//skip empty lines
					std::getline(in, line);
				int l = 0;
				nums.str(line);
				while(nums >> num)
				{
					double z;
					string_to_number(num, z);
					Z(k, l) = z;

					l++;
				}
				nums.clear();
				nums.str(string());
			}
			layer_boundary.push_back(Layer_boundary(X, Y, Z));
			X.clear();
			Y.clear();
			Z.clear();
		}

	}
	in.close();

	/*make spline for each layer boundary*/
	layer_boundary_spl.resize(layer_boundary.size());
	for(int i = 0; i < layer_boundary.size(); i++)
	{
		layer_boundary_spl[i] = Spline2D_cubic(
			layer_boundary[i].X_,
			layer_boundary[i].Y_,
			layer_boundary[i].Z_);

		/*make primitive mesh*/
		for(int l = 0; l < layer_boundary[i].nx_; l++)
		{
			X_primitive.insert(layer_boundary[i].X_[l]);
		}
		for(int l = 0; l < layer_boundary[i].ny_; l++)
		{
			Y_primitive.insert(layer_boundary[i].Y_[l]);
		}

	}
	X.~vector();
	Y.~vector();
	Z.~Matrix();
}

void MeshBuilder::set_anomalies()
{
	set_anomalies(default_file_anomalies);
}

void MeshBuilder::set_anomalies(const char * file_name)
{
	string line;		//line read from file
	string num;			//string containing one number
	stringstream nums;	//string containing all numbers from line
	ifstream in;
	in.open(file_name, ifstream::in);

	int n_layer;
	vector<double> x;
	vector<double> y;

	if(in.is_open())
	{
		/*read number of layers*/
		std::getline(in, num);

		while(num == "")	//skip empty lines
			std::getline(in, num);
		string_to_number(num, n_anomalies);

		/*read layer boundary coordinates*/
		for(int i = 0; i < n_anomalies; i++)
		{
			//read layer number
			std::getline(in, line);
			while(line == "")	//skip empty lines
				std::getline(in, line);
			nums.str(line);
			nums >> num;
			string_to_number(num, n_layer);
			nums.clear();
			nums.str(string());

			//read x-coordinates
			std::getline(in, line);
			while(line == "")	//skip empty lines
				std::getline(in, line);
			nums.str(line);
			while(nums >> num)
			{
				double x_;
				string_to_number(num, x_);
				x.push_back(x_);

				//add anomaly coordinates to primitive mesh
				X_primitive.insert(x_);
			}
			nums.clear();
			nums.str(string());

			//read y-coordinates
			std::getline(in, line);
			while(line == "")	//skip empty lines
				std::getline(in, line);
			nums.str(line);
			while(nums >> num)
			{
				double y_;
				string_to_number(num, y_);
				y.push_back(y_);

				//add anomaly coordinates to primitive mesh
				Y_primitive.insert(y_);
			}
			nums.clear();
			nums.str(string());
	
			anomalies.push_back(Anomaly(n_layer, x[0], x[1], y[0], y[1]));
		}
	}
	in.close();

	x.~vector();
	y.~vector();
}

void MeshBuilder::set_fragmentation()
{
	set_fragmentation(default_file_fragmentation);
}

void MeshBuilder::set_fragmentation(const char * file_name)
{
	string line;		//line read from file
	string num;			//string containing one number
	stringstream nums;	//string containing all numbers from line
	ifstream in;
	in.open(file_name, ifstream::in);

	if(in.is_open())
	{
		//read x-fragmentation
		std::getline(in, line);
		while(line == "")	//skip empty lines
			std::getline(in, line);
		nums.str(line);
		while(nums >> num)
		{
			int n;
			double coeff;
			string_to_number(num, n);
			nums >> num;
			string_to_number(num, coeff);
			X_fragments.push_back(Fragmentation_info(n, coeff));
		}
		nums.clear();
		nums.str(string());

		//read y-fragmentation
		std::getline(in, line);
		while(line == "")	//skip empty lines
			std::getline(in, line);
		nums.str(line);
		while(nums >> num)
		{
			int n;
			double coeff;
			string_to_number(num, n);
			nums >> num;
			string_to_number(num, coeff);
			Y_fragments.push_back(Fragmentation_info(n, coeff));
		}
		nums.clear();
		nums.str(string());

		//read z-fragmentation
		std::getline(in, line);
		while(line == "")	//skip empty lines
			std::getline(in, line);
		nums.str(line);
		while(nums >> num)
		{
			int n;
			double coeff;
			string_to_number(num, n);
			nums >> num;
			string_to_number(num, coeff);
			Z_fragments.push_back(Fragmentation_info(n, coeff));
		}
		nums.clear();
		nums.str(string());
	}
	in.close();
}

void MeshBuilder::set_formula()
{
	set_formula(default_file_formula);
}

void MeshBuilder::set_formula(const char * file_name)
{
	string line;		//line read from file
	string num;			//string containing one number
	stringstream nums;	//string containing all numbers from line
	ifstream in;
	in.open(file_name, ifstream::in);

	if(in.is_open())
	{
		//read layer formulas
		for(int i = 0; i < n_layers; i++)
		{
			std::getline(in, line);
			while(line == "")	//skip empty lines
				std::getline(in, line);
			nums.str(line);
			nums >> num;
			int number;
			string_to_number(num, number);
			formula_layer.push_back(number);

			nums.clear();
			nums.str(string());
		}

		//read layer formulas
		for(int i = 0; i < n_anomalies; i++)
		{
			std::getline(in, line);
			while(line == "")	//skip empty lines
				std::getline(in, line);
			nums.str(line);
			nums >> num;
			int number;
			string_to_number(num, number);
			formula_anomaly.push_back(number);

			nums.clear();
			nums.str(string());
		}
	}
	in.close();
}

void MeshBuilder::get_mesh()
{
	get_mesh(default_file_nodes, default_file_fes, default_file_firstBCs);
}

void MeshBuilder::get_mesh(const char * file_name_nodes, const char * file_name_fes, const char * file_name_firstBCs)
{
	ofstream ostr;
	/*print nodes to file*/
	ostr.open(file_name_nodes);
	ostr << n_nodes << endl;
	for(int i = 0; i < n_nodes; i++)
	{
		nodes[i].print(ostr, 16);
	}
	ostr.close();

	/*print fes to file*/
	ostr.open(file_name_fes);
	ostr << n_fes << endl;
	for(int i = 0; i < n_fes; i++)
	{
		fes[i].print(ostr);
	}
	ostr.close();

	/*print firstBCs to file*/
	ostr.open(file_name_firstBCs);
	ostr << n_firstBCs << endl;
	for(int i = 0; i < n_firstBCs; i++)
	{
		firstBCs[i].print(ostr);
	}
	ostr.close();
}

void MeshBuilder::get_mesh(vector<Node3D>& nodes, vector<FE>& fes, vector<FirstBC>& firstBC)
{
	nodes.clear();
	fes.clear();
	firstBC.clear();

	for(int i = 0; i < n_nodes; i++)
	{
		nodes.push_back(this->nodes[i]);
	}
	for(int i = 0; i < n_fes; i++)
	{
		fes.push_back(this->fes[i]);
	}
	for(int i = 0; i < n_firstBCs; i++)
	{
		firstBCs.push_back(this->firstBCs[i]);
	}
}







/*----------------------------*/
/*Secondary functions*/
/*----------------------------*/

void Layer_boundary::display()
{
	display_stlvector(X_);
	display_stlvector(Y_);
	Z_.display();
}

void Anomaly::display()
{
	cout << fixed;
	cout.precision(DISPLAY_PRECISION);
	cout << "#layer containing anomaly: " << n_layer << endl;
	cout << x0 << " " << xn << ", " << y0 << " " << yn << endl;
}

void Fragmentation_info::display()
{
	cout << fixed;
	cout.precision(DISPLAY_PRECISION);
	cout << n << " " << coeff << " " << sign << endl;
}