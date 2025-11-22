#include <iostream>

using byte = unsigned char;

bool isSameCell(std::pair<byte, byte> a, std::pair<byte, byte> b) {
	return (a.first == b.first) && (a.second == b.second);
}
int main() {

	std::pair<byte, byte> A, B;
	std::cout << "enter coordinates positionA" << std::endl;
	std::cin >> A.first >> A.second;
	std::cout << "enter coordinates positionB" << std::endl;
	std::cin >> B.first >> B.second;
	if (!isSameCell(A, B)) {

		if ((A.first == B.first) || (A.second == B.second)) {
			std::cout << "The rook is threatening" << std::endl;

		}
		if (abs(A.first - B.first) == abs(A.second - B.second)) {
			std::cout << "The bishop is threatening" << std::endl;
		}

		if ((abs(A.first - B.first) <= 1) && (abs(A.second - B.second) <= 1)) {
			std::cout << "The king can move to square B" << std::endl;
		}

		if (((A.first == B.first) || (A.second == B.second)) || (abs(A.first - B.first) == abs(A.second - B.second))) {
			std::cout << "The queen is threatening" << std::endl;
		}

		if ((A.first == B.first) && (A.second + 1 == B.second)) {
			std::cout << "usual pawn move" << std::endl;
		}

		if ((abs(A.first - B.first) == 1) && (A.second + 1 == B.second)) {
			std::cout << "pawn move when taking a piece" << std::endl;
		}
	}

}
