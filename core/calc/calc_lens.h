// ************************************************************************** //
//
//  Steca2: stress and texture calculator
//
//! @file      core/calc/calc_lens.h
//! @brief     Defines LensBase, ImageLens, DatasetLens
//!
//! @homepage  https://github.com/scgmlz/Steca2
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2017
//! @authors   Scientific Computing Group at MLZ (see CITATION, MAINTAINER)
//
// ************************************************************************** //

#ifndef CALC_LENS_H
#define CALC_LENS_H

#include "data/dataset.h"
#include "typ/geometry.h"
#include "data/image_transform.h"

namespace calc {

//! View the dataset through a lens

class LensBase {
public:
    LensBase(
        Session const&, Datasets const&, bool trans, bool cut,
        ImageTransform const&, ImageCut const&);
    virtual ~LensBase() {}
    virtual size2d size() const = 0;

protected:
    size2d transCutSize(size2d) const;

    void doTrans(uint& i, uint& j) const;
    void doCut(uint& i, uint& j) const;

    Session const& session_;
    Datasets const& datasets_;
    bool trans_, cut_;
    ImageTransform imageTransform_;
    ImageCut imageCut_;
    Image const* intensCorr_;
};

class ImageLens final : public LensBase {
public:
    ImageLens(Session const&, Image const&, Datasets const&, bool trans, bool cut);

    size2d size() const;

    inten_t imageInten(uint i, uint j) const;

    Range const& rgeInten(bool fixed) const;

private:
    Image const& image_;

    mutable Range rgeInten_;
};


typedef QSharedPointer<ImageLens> shp_ImageLens;

class DatasetLens final : public LensBase {
public:
    DatasetLens(
        Session const&, Dataset const&, Datasets const&, eNorm, bool trans,
        bool cut, ImageTransform const&, ImageCut const&);

    size2d size() const;

    Range rgeGma() const;
    Range rgeGmaFull() const;
    Range rgeTth() const;
    Range rgeInten() const;

    Curve makeCurve() const;
    Curve makeCurve(Range const&) const;

    Dataset const& dataset() const { return dataset_; }

private:
    void setNorm(eNorm);
    inten_t normFactor_;

    Dataset const& dataset_;
};

typedef QSharedPointer<DatasetLens> shp_DatasetLens;

} // namespace calc

#endif // CALC_LENS_H
