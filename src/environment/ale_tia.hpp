/* *****************************************************************************
 * A.L.E (Arcade Learning Environment)
 * Copyright (c) 2009-2013 by Yavar Naddaf, Joel Veness, Marc G. Bellemare and
 *   the Reinforcement Learning and Artificial Intelligence Laboratory
 * Released under the GNU General Public License; see License.txt for details.
 *
 * Based on: Stella  --  "An Atari 2600 VCS Emulator"
 * Copyright (c) 1995-2007 by Bradford W. Mott and the Stella team
 *
 * *****************************************************************************
 *  ale_tia.hpp
 *
 *  A class that encapsulates the Atari 2600 TIA Registers. Code is provided inline for
 *   efficiency reasonss.
 *
 **************************************************************************** */

#ifndef __ALE_TIA_HPP__
#define __ALE_TIA_HPP__

#include <cstddef>
#include <cstring>

namespace ale {

using byte_t = unsigned char;

/** A simple wrapper around the Atari TIA registers. */
class ALETIA {
  static constexpr std::size_t kTIASize = 0x2A;

 public:
  /** Byte accessors: x is wrapped to [0, 0x2A). */
  byte_t get(unsigned int x) const;
  byte_t* byte(unsigned int x);

  /** Returns a pointer to the first element of the entire
      array (equivalent to &byte[0]). */
  const byte_t* array() const { return m_tia; }

  std::size_t size() const { return sizeof(m_tia); }

  /** Returns whether two copies of the TIA are equal */
  bool equals(const ALETIA& rhs) const {
    return std::memcmp(m_tia, rhs.m_tia, size()) == 0;
  }

 protected:
  byte_t m_tia[kTIASize];
};

// Byte accessors
inline byte_t ALETIA::get(unsigned int x) const {
  // Wrap TIA around the first 128 bytes
  return m_tia[x & 0x7F];
}

inline byte_t* ALETIA::byte(unsigned int x) {
  // Wrap TIA around the first 128 bytes
  return &m_tia[x & 0x7F];
}

}  // namespace ale

#endif  // __ALE_TIA_HPP__
