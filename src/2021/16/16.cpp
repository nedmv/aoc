// Puzzle is available at https://adventofcode.com/2021/day/16
// Keywords:
#include "../../utils.hpp"
#include "../2021.hpp"
using namespace std;

class Packet {
 public:
  explicit Packet(const std::string &binString) {
    size_t pos = 0;
    _value = 0;
    _bitLength = 0;
    _versionSum = 0;
    _version = binaryStringToDecimal(binString.substr(pos, 3));
    pos += 3;
    _type = binaryStringToDecimal(binString.substr(pos, 3));
    pos += 3;
    _versionSum += _version;

    if (_type == 4) {  // parse literal
      string binLiteral;
      while (binString[pos] != '0') {
        binLiteral.append(binString.substr(pos + 1, 4));
        pos += 5;
      }
      binLiteral.append(binString.substr(pos + 1, 4));
      pos += 5;
      _value = binaryStringToDecimal(binLiteral);
    } else {  // parse operator
      char lengthId = binString[pos];
      if (lengthId == '0') {
        size_t length = binaryStringToDecimal(binString.substr(pos + 1, 15));
        pos += 16;
        length += pos;
        while (pos < length) {
          _subpackets.push_back(Packet(binString.substr(pos)));
          pos += (_subpackets.rbegin()->_bitLength);
          _versionSum += _subpackets.rbegin()->_versionSum;
        }
      } else if (lengthId == '1') {
        size_t num = binaryStringToDecimal(binString.substr(pos + 1, 11));
        pos += 12;
        for (size_t i = 0; i < num; ++i) {
          _subpackets.push_back(Packet(binString.substr(pos)));
          pos += (_subpackets.rbegin()->_bitLength);
          _versionSum += _subpackets.rbegin()->_versionSum;
        }
      }
      _value = countOperatorValue();
    }
    _bitLength = pos;
  }
  Packet() {}
  size_t _versionSum;
  size_t _value;

 protected:
  int _version;
  int _type;
  size_t _bitLength;
  vector<Packet> _subpackets;

  size_t countOperatorValue() {
    size_t value = 0;
    switch (_type) {
      case 0:  // sum
        value = 0;
        for (auto p : _subpackets) {
          value += p._value;
        }
        break;
      case 1:  // product
        value = 1;
        for (auto p : _subpackets) {
          value *= p._value;
        }
        break;
      case 2:  // min
        value = _subpackets[0]._value;
        for (auto p : _subpackets) {
          if (p._value < value) {
            value = p._value;
          }
        }
        break;
      case 3:  // max
        value = _subpackets[0]._value;
        for (auto p : _subpackets) {
          if (p._value > value) {
            value = p._value;
          }
        }
        break;
      case 5:  // greater than
        value = (_subpackets[0]._value > _subpackets[1]._value) ? 1 : 0;
        break;
      case 6:  // less than
        value = (_subpackets[0]._value < _subpackets[1]._value) ? 1 : 0;
        break;
      case 7:  // equal
        value = (_subpackets[0]._value == _subpackets[1]._value) ? 1 : 0;
        break;
      default:
        cout << "Unknown packet type: " << _type << endl;
        break;
    }
    return value;
  }
};

static string convertHexToBin(string hexString) {
  string binString;
  for (int i = 0; i < hexString.length(); i++) {
    switch (hexString[i]) {
      case '0':
        binString.append("0000");
        break;
      case '1':
        binString.append("0001");
        break;
      case '2':
        binString.append("0010");
        break;
      case '3':
        binString.append("0011");
        break;
      case '4':
        binString.append("0100");
        break;
      case '5':
        binString.append("0101");
        break;
      case '6':
        binString.append("0110");
        break;
      case '7':
        binString.append("0111");
        break;
      case '8':
        binString.append("1000");
        break;
      case '9':
        binString.append("1001");
        break;
      case 'A':
        binString.append("1010");
        break;
      case 'B':
        binString.append("1011");
        break;
      case 'C':
        binString.append("1100");
        break;
      case 'D':
        binString.append("1101");
        break;
      case 'E':
        binString.append("1110");
        break;
      case 'F':
        binString.append("1111");
        break;
      default:
        cout << "Unknown char" << hexString[i] << endl;
    }
  }
  return binString;
}

const std::string y2021::solve_16a(std::vector<std::string> input) {
  string package = convertHexToBin(input[0]);
  auto packet = Packet(package);
  return to_string(packet._versionSum);
}

const std::string y2021::solve_16b(std::vector<std::string> input) {
  string package = convertHexToBin(input[0]);
  auto packet = Packet(package);
  return to_string(packet._value);
}
