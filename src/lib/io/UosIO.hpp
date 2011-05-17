/**
 * UosIO.h
 *
 *  @date 11.05.2011
 *  @author Thomas Wiemann
 */

#ifndef UOSIO_H_
#define UOSIO_H_

#include <string>
#include <iomanip>
#include <iostream>
#include <cmath>
#include <fstream>

using std::string;
using std::fstream;

namespace lssr
{
/**
 * @brief An input class for laser scans in UOS 3d format.
 *
 * Per default, this class tries to read all scans in the given
 * directory. If you don't want to specify which scans to read,
 * use the \ref{setFirstScan} and \ref{setLastScan} methods to
 * specify an interval to read. If .frame files are present, the
 * single scans will be transformed according to the last
 * transformation in the file. If no .frame file are present, the
 * .pose files will be sued to transform the scans.
 */
template<typename T>
class UosIO
{
public:

    /**
     * @brief Contructor.
     */
    UosIO() : m_firstScan(-1), m_lastScan(-1) {}

    /**
     * @brief Reads all scans or an specified range of scans
     *        from the given directory
     *
     * @param dir       A directory containing scans in UOS format.
     * @return          An indexed array of scan points
     */
    T** read(string dir, size_t &n);

    /**
     * @brief Defines the first scan to read
     * @param n         The first scan to read
     */
    void setFirstScan(int n) { m_firstScan = n;}

    /**
     * @brief Defines the last scan to read
     * @param n         The last scan to read
     */
    void setLastScan(int n) {m_lastScan = n;}

private:

    /**
     * @brief Reads scans from \ref{first} to \ref{last} in new UOS format.
     * @param dir       The directory path
     * @param first     The first scan to read
     * @param last      The last scan to read
     * @return          All read data points
     */
    T** readNewFormat(string dir, int first, int last, size_t &n);

    /**
     * @brief Reads scans from \ref{first} to \ref{last} in old UOS format.
     * @param dir       The directory path
     * @param first     The first scan to read
     * @param last      The last scan to read
     * @return          All read data points
     */
    T** readOldFormat(string dir, int first, int last, size_t &n);

    /**
     * @brief Creates a transformation matrix from given frame file
     *
     * @param frameFile
     * @return          A matrix representing the final transformation
     *                  from a frame file
     */
    Matrix4<float> parseFrameFile(ifstream& frameFile);

    inline std::string to_string(const T& t, int width)
    {
      stringstream ss;
      ss << std::setfill('0') << std::setw(width) << t;
      return ss.str();
    }

    inline std::string to_string(const T& t)
    {
      stringstream ss;
      ss << t;
      return ss.str();
    }

    /**
     * Converts an angle (given in deg) to rad
     *
     * @param deg integer indicating, whether the figure to be drawn to show
     * the clusters should be circles (0) or rectangles(1)
     *
     * @return the clustered image, with the clusters marked by colored figures
     *
     */
    inline T rad(const T deg)
    {
      return ( (2 * M_PI * deg) / 360 );
    }

    /**
     * Converts an angle (given in rad) to deg
     *
     * @param rad  angle in rad
     * @return     angle in deg
     */
    inline T deg(const T rad)
    {
      return ( (rad * 360) / (2 * M_PI) );
    }


    /// The first scan to read (or -1 if all scans should be processed)
    int     m_firstScan;

    /// The last scan to read (or -1 if all scans should be processed)
    int     m_lastScan;
};

} // namespace lssr

#include "UosIO.tcc"

#endif /* UOSIO_H_ */
