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
 *  ale_cpu.hpp
 *
 *  A class that encapsulates the Atari 2600 CPU Registers. Code is provided inline for
 *   efficiency reasonss.
 *
 **************************************************************************** */

#ifndef __ALE_CPU_HPP__
#define __ALE_CPU_HPP__

#include <cstddef>
#include <cstring>

namespace ale {

using byte_t = unsigned char;

/** A simple wrapper around the Atari CPU registers. */
class ALECPU {
  static constexpr std::size_t kCPUSize = 8;

 public:
  /** Byte accessors: x is wrapped to [0, 8). */
  byte_t get(unsigned int x) const;
  byte_t* byte(unsigned int x);

  /** Returns a pointer to the first element of the entire
      array (equivalent to &byte[0]). */
  const byte_t* array() const { return m_cpu; }

  std::size_t size() const { return sizeof(m_cpu); }

  /** Returns whether two copies of the CPU are equal */
  bool equals(const ALECPU& rhs) const {
    return std::memcmp(m_cpu, rhs.m_cpu, size()) == 0;
  }

 protected:
  byte_t m_cpu[kCPUSize];
};

// Byte accessors
inline byte_t ALECPU::get(unsigned int x) const {
  // Wrap CPU around the first 128 bytes
  return m_cpu[x & 0xF];
}

inline byte_t* ALECPU::byte(unsigned int x) {
  // Wrap CPU around the first 128 bytes
  return &m_cpu[x & 0xF];
}

}  // namespace ale

#endif  // __ALE_CPU_HPP__
