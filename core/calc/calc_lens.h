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

#include "data/data_dataset.h"
#include "typ/geometry.h"
#include "typ/image_transform.h"

namespace calc {

//! View the dataset through a lens

class LensBase {
public:
    LensBase(
        core::Session const&, data::Datasets const&, bool trans, bool cut,
        typ::ImageTransform const&, typ::ImageCut const&);

    virtual typ::size2d size() const = 0;

protected:
    typ::size2d transCutSize(typ::size2d) const;

    void doTrans(uint& i, uint& j) const;
    void doCut(uint& i, uint& j) const;

    core::Session const& session_;
    data::Datasets const& datasets_;
    bool trans_, cut_;
    typ::ImageTransform imageTransform_;
    typ::ImageCut imageCut_;
    typ::Image const* intensCorr_;
};

class ImageLens final : public LensBase {
private:
    using super = LensBase;
public:
    ImageLens(core::Session const&, typ::Image const&, data::Datasets const&, bool trans, bool cut);

    typ::size2d size() const;

    inten_t imageInten(uint i, uint j) const;

    inten_rge const& rgeInten(bool fixed) const;

private:
    typ::Image const& image_;

    mutable inten_rge rgeInten_;
};

typedef QSharedPointer<ImageLens> shp_ImageLens;

class DatasetLens final : public LensBase {
private:
    using super = LensBase;
public:
    DatasetLens(
        core::Session const&, data::Dataset const&, data::Datasets const&, eNorm, bool trans,
        bool cut, typ::ImageTransform const&, typ::ImageCut const&);

    typ::size2d size() const;

    gma_rge rgeGma() const;
    gma_rge rgeGmaFull() const;
    tth_rge rgeTth() const;
    inten_rge rgeInten() const;

    typ::Curve makeCurve() const;
    typ::Curve makeCurve(gma_rge const&) const;

    data::Dataset const& dataset() const { return dataset_; }

private:
    void setNorm(eNorm);
    inten_t normFactor_;

    data::Dataset const& dataset_;
};

typedef QSharedPointer<DatasetLens> shp_DatasetLens;

} //namespace calc

#endif // CALC_LENS_H
