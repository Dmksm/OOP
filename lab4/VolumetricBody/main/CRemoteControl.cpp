#include "CRemoteControl.h"
#include "CBody.h"
#include "CCone.h"
#include "CCylinder.h"
#include "CParallelepiped.h"
#include "CSphere.h"
#include "CCompound.h"


using namespace std;
using namespace std::placeholders;

const double WATER_DENSITY = 1000;
const double GRAVITATIONAL_CONSTANT = 10;

const string densityParamName = "density";
const string baseRadiusParamName = "baseradius";
const string heightParamName = "height";
const string radiusParamName = "radius";
const string widthParamName = "width";
const string depthParamName = "depth";

struct Convert
{
	unsigned char operator()(unsigned char const& c)
	{
		return tolower(c);
	}
};

std::shared_ptr<CBody>* GetBodyPointer(std::istream& input, std::string& bodyName);

void PushBody(std::istream& input, std::vector<std::shared_ptr<CBody>>& bodies,
	std::string& bodyName, std::string msg)
{
	while (!input.eof() && !input.fail() && (std::cout << msg)
		&& (input >> bodyName))
	{
		std::transform(bodyName.begin(), bodyName.end(), bodyName.begin(), Convert());

		if ((bodyName != "compound") && (bodyName != "cone") && (bodyName != "cylinder")
			&& (bodyName != "parallelepiped") && (bodyName != "sphere"))
		{
			return;
		}

		auto pointer = GetBodyPointer(input, bodyName);
		if (pointer == nullptr)
		{
			bodies.clear();
			return;
		}
		std::cout << "Success!" << std::endl;
		bodies.push_back(*pointer);
	}
}

std::shared_ptr<CBody>* GetBodyPointer(std::istream& input, std::string& bodyName)
{
	if (bodyName == "compound")
	{
		std::vector<std::shared_ptr<CBody>> compoudBody;
		std::string msg = "Enter body name child of compound body: ";
		PushBody(input, compoudBody, bodyName, msg);
		if (compoudBody.empty())
		{
			return new shared_ptr<CBody>();
		}
		return new shared_ptr<CBody>(new CCompound(compoudBody));
	}

	double baseRadius, height, width, depth, radius;
	std::string val;
	std::cout << "Enter (density): ";
	input >> val;
	double density = std::stod(val);

	if (bodyName == "cone")
	{
		std::cout << "Enter (base radius) and (height) separated by a space: ";
		input >> val;
		baseRadius = std::stod(val);

		input >> val;
		height = std::stod(val);

		return new shared_ptr<CBody>(new CCone(density, baseRadius, height));
	}

	if (bodyName == "cylinder")
	{
		std::cout << "Enter (base radius) and (height) separated by a space: ";
		input >> val;
		baseRadius = std::stod(val);

		input >> val;
		height = std::stod(val);

		return new shared_ptr<CBody>(new CCylinder(density, baseRadius, height));
	}

	if (bodyName == "parallelepiped")
	{
		std::cout << "Enter (width) and (height) and (depth) separated by a space: ";
		input >> val;
		width = std::stod(val);

		input >> val;
		height = std::stod(val);

		input >> val;
		depth = std::stod(val);

		return new shared_ptr<CBody>(new CParallelepiped(density, width, height, depth));
	}

	if (bodyName == "sphere")
	{
		std::cout << "Enter (radius): ";
		input >> val;
		radius = std::stod(val);

		return new shared_ptr<CBody>(new CSphere(density, radius));
	}

	std::cout << "Undefined body name!" << endl;
	return new shared_ptr<CBody>();
}

CRemoteControl::CRemoteControl(std::vector<std::shared_ptr<CBody>>& bodies, std::istream& input, std::ostream& output)
	: m_bodies(bodies)
	, m_input(input)
	, m_output(output)
	, m_actionMap({
		  { "gethighestmassbody", bind(&CRemoteControl::GetHighestMassBody, this) },
		  { "getlighterbodyinwater", bind(&CRemoteControl::GetLighterBodyInWater, this) },
		  { "info", bind(&CRemoteControl::Info, this) },
		  { "initbodies", bind(&CRemoteControl::InitBodies, this) },
		  { "help", bind(&CRemoteControl::Help, this) } //
	  })
{
}

bool CRemoteControl::Help()
{
	m_output << "gethighestmassbody" << std::endl << "getlighterbodyinwater" << std::endl <<
		"info" << std::endl << "initbodies" << std::endl << "help" << std::endl;
	return true;
}
bool CRemoteControl::HandleCommand()
{
	string commandLine;
	getline(m_input, commandLine);
	istringstream strm(commandLine);

	string action;
	strm >> action;
	std::transform(action.begin(), action.end(), action.begin(), Convert());  //переименовать в toLower

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		return it->second(strm);
	}

	return false;
}

bool CRemoteControl::InitBodies()
{
	std::string bodyName, msg = "Enter body name: ";
	std::cout << "To exit, enter non-reserved body name" << std::endl;

	PushBody(m_input, m_bodies, bodyName, msg);

	return true;
}

bool CRemoteControl::GetHighestMassBody()
{
	if (m_bodies.empty())
	{
		std::cout << "Bodies is empty at now" << std::endl;
		return true;
	}
	
	std::cout << "Highest mass body:" << std::endl;
	shared_ptr<CBody> maxMassBody = m_bodies.front();
	for (auto body : m_bodies)
	{
		if ((*body).GetMass() > (*maxMassBody).GetMass())
		{
			maxMassBody = body;
		}
	}
	std::cout << " " << (*maxMassBody).ToString() << std::endl;
	return true;
}

bool CRemoteControl::GetLighterBodyInWater()
{
	if (m_bodies.empty())
	{
		std::cout << "Bodies is empty at now" << std::endl;
		return true;
	}

	std::cout << "Lighter body in water:" << std::endl;
	std::map<shared_ptr<CBody>, double> lighterBodyInfo;
	shared_ptr<CBody> firstBody = m_bodies.front();
	lighterBodyInfo.insert(
		std::make_pair(firstBody,
					(firstBody->GetDensity() - WATER_DENSITY) * 
					GRAVITATIONAL_CONSTANT * firstBody->GetVolume())
		);
	for (auto body : m_bodies)
	{
		double valueUnderWater = (body->GetDensity() - WATER_DENSITY) * 
			GRAVITATIONAL_CONSTANT * body->GetVolume();
		if (valueUnderWater > lighterBodyInfo.begin()->second)
		{
			lighterBodyInfo.begin()->second = valueUnderWater;
		}
	}
	std::cout << " " << lighterBodyInfo.begin()->first->ToString() << std::endl;
	return true;
}

bool CRemoteControl::Info()
{
	std::cout << "All bodies:" << std::endl;
	for (auto body : m_bodies)
	{
		std::cout << " " << (*body).ToString();
	}
	std::cout << std::endl;
	return true;
}