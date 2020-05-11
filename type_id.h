#ifndef TYPE_ID_H_
#define TYPE_ID_H_

inline int type_id_seq = 0;
template< typename T > inline const int type_id = type_id_seq++;

#endif  // TYPE_ID_H_
