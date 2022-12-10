//######################################################
// Project: General Hospital Pre-Triage Application  ###
//######################################################

#ifndef SDDS_IOABLE_H_
#define SDDS_IOABLE_H_
namespace sdds
{
	class IOAble {
	public:
		virtual std::ostream& csvWrite(std::ostream& ostr = std::cout) const = 0;
		virtual std::istream& csvRead(std::istream& istr = std::cin) = 0;
		virtual std::ostream& write(std::ostream& ostr = std::cout) const = 0;
		virtual std::istream& read(std::istream& istr = std::cin) = 0;
		virtual ~IOAble();
	};
	std::istream& operator>>(std::istream& istr, IOAble& I);
	std::ostream& operator<<(std::ostream& ostr, const IOAble& I);
}
#endif // !SDDS_IOABLE_H_