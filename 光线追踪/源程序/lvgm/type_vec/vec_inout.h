//
// Created by hdutyq on 2019/5/30.
//

#ifndef UNTITLED_VEC_INOUT_H
#define UNTITLED_VEC_INOUT_H

#endif //UNTITLED_VEC_INOUT_H
#pragma once



# ifdef    VEC_OUT

    template<typename T>
        std::ostream& operator<<(std::ostream& cout, const lvgm::vec2<T>& v)
            {
            cout << "[ " << v.x() << ", " << v.y() << " ]";
            return cout;
            }

    template<typename T>
        std::ostream& operator<<(std::ostream& cout, const lvgm::vec3<T>& v)
            {
            cout << "[ " << v.x() << ", " << v.y() << ", " << v.z() << " ]";
            return cout;
            }

    template<typename T>
        std::ostream& operator<<(std::ostream& cout, const lvgm::vec4<T>& v)
        {
            cout << "[ " << v.x() << ", " << v.y() << ", " << v.z() << v.w() << " ]";
            return cout;
        }

#endif

# ifdef VEC2_OUT

    template<typename T>
        std::ostream& operator<<(std::ostream& cout, const lvgm::vec2<T>& v)
            {
            cout << "[ " << v.x() << ", " << v.y() << " ]";
            return cout;
            }

#endif

# ifdef VEC3_OUT

    template<typename T>
        std::ostream& operator<<(std::ostream& cout, const lvgm::vec3<T>& v)
            {
            cout << "[ " << v.x() << ", " << v.y() << ", " << v.z() << " ]";
            return cout;
            }

#endif

# ifdef VEC4_OUT

    template<typename T>
        std::ostream& operator<<(std::ostream& cout, const lvgm::vec4<T>& v)
            {
            cout << "[ " << v.x() << ", " << v.y() << ", " << v.z() << v.w() << " ]";
            return cout;
            }

#endif
