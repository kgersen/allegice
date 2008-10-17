/*
**  Copyright (C) 2008 FAZ Dev Team. All Rights Reserved.
**
**  File:    constants.h
**
**  Author: KGJV 
**
**  Description:
**      global constants extracted from Utility.h to allow standalone usage of IGC (see igc/igc_static.h)
**
**  History:
*/
#ifndef CONSTANTS_H
#define CONSTANTS_H


// These constants correspond to the maximum length of a file name or a 
// player name. They should correspond to the maximum lengths in the SQL 
// database (for Name and FileName custom data types). Longer names are 
// handled via truncation. DB versions do not include the NULL terminator
const int c_cbFileNameDB    = 12; // keep in sync with 
const int c_cbDescriptionDB = 200;
const int c_cbNameDB        = 24;
const int c_cbLocAbrevDB    = 8;
const int c_cbFileName      = c_cbFileNameDB    + 1;
const int c_cbDescription   = c_cbDescriptionDB + 1;
const int c_cbName          = c_cbNameDB        + 1;
const int c_cbLocAbrev      = c_cbLocAbrevDB    + 1;
const int c_cbCDKey         = 32 + 1; // TODO: fill in the correct length
const int c_cbPassportName  = 256 + 1;

// BytePercentage moved here, it's widely used.
class   BytePercentage
{
    public:
        enum
        {
            Divisor = 240   //Use 240 since it has so many nice factors (2, 3, 4, 5, 10, etc.) 
        };

        BytePercentage(void)
        {
        }

        BytePercentage(const BytePercentage& p)
        :
            m_percentage(p.m_percentage)
        {
        }

        BytePercentage(float f)
        :
            m_percentage((unsigned char)(f * (float)Divisor + 0.5f))
        {
            assert ((f * (float)Divisor + 0.5f) >= 0.0f);
            assert ((f * (float)Divisor + 0.5f) < (float)(Divisor + 1));
        }

        unsigned char   GetChar(void) const
        {
            return m_percentage;
        }
        void            SetChar(unsigned char p)
        {
            m_percentage = p;
        }

        BytePercentage& operator = (float f)
        {
            assert ((f * (float)Divisor + 0.5f) >= 0.0f);
            assert ((f * (float)Divisor + 0.5f) < (float)(Divisor + 1));
            m_percentage = (unsigned char)(f * (float)Divisor + 0.5f);
            return *this;
        }

        operator float (void) const
        {
            return ((float)m_percentage) / ((float)Divisor);
        }

    private:
        unsigned char   m_percentage;
};

// Rotation
class Rotation
{
    public:
        Rotation(void);
        Rotation(float x, float y, float z, float a)
        :
            m_axis(x, y, z),
            m_angle(a)
        {
        }
        Rotation(const Vector& xyz, float a)
        :
            m_axis(xyz),
            m_angle(a)
        {
        }
        //Rotation(const Rotation&);

        void    reset(void);

        void        set(const Vector& axis,
                        float         angle);

        Rotation&   operator = (const Rotation&);

        inline float    x(void) const
        {
            return m_axis.x;
        }

        inline float    y(void) const
        {
            return m_axis.y;
        }

        inline float    z(void) const
        {
            return m_axis.z;
        }

        inline float    angle(void) const
        {
            return m_angle;
        }

        inline const Vector&   axis(void) const
        {
            return m_axis;
        }

        void        axis(const Vector&  v);
        void        angle(float  r);
        void        x(float  t);
        void        y(float  t);
        void        z(float  t);

    private:
        Vector  m_axis;
        float   m_angle;
};


#endif //CONSTANTS_H