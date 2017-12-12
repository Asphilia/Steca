// ************************************************************************** //
//
//  Steca2: stress and texture calculator
//
//! @file      core/typ/hash.h
//! @brief     Defines ...
//!
//! @homepage  https://github.com/scgmlz/Steca2
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ (see CITATION, MAINTAINER)
//
// ************************************************************************** //

#ifndef HASH_H
#define HASH_H

namespace typ {

template <typename Key, typename T>
class hash : protected QHash<Key, T> {
    using super = QHash<Key,T>;
public:
    using super::clear;
};

template <typename Key, typename Tp>
class owning_hash : protected hash<Key, Tp> {
    using super = hash<Key,Tp>;
public:
    ~owning_hash() { clear(); }

    void clear() {
        for (auto* v : QHash<Key, Tp>::values())
            delete v;
        super::clear();
    }

    void insert(Key const& key, not_null<Tp> t) {
        remove(key);
        super::insert(key, t);
    }

    bool remove(Key const& key) {
        Tp t = take(key);
        delete t;
        return nullptr != t;
    }

    Tp value(Key const& key) { return super::value(key); }

    Tp take(Key const& key) { return super::take(key); }
};

} // namespace typ

#endif // HASH_H