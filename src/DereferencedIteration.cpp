struct DereferencedIteration
{
	DereferencedIteration(const bool defaulted = true);

	const bool defaulted;
};

DereferencedIteration::DereferencedIteration(const bool defaulted)
	: defaulted(defaulted)
{
}