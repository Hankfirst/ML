#pragma once
#include "Layer.h"
#include "FlattenLayer.h"
namespace FengML
{
    class Tensor3DLayer: public Layer<Tensor3>
    {
    public:
        Tensor3DLayer(): flattenLayer(nullptr)
        {
        }
        Tensor3DLayer(typename Tensor3::DT dim) :Layer<Tensor3>(dim),
            flattenLayer(nullptr)
        {

        }
        virtual std::shared_ptr<LayerBase> Next()
        {
            if (nextLayer == nullptr)
            {
                return flattenLayer;
            }

            return nextLayer;
        }

        virtual std::shared_ptr<FlattenLayer> Flatten();

        virtual typename Tensor3::DT Dim3()
        {
            return dim;
        }

        virtual typename Tensor3::DataType& GetData3D()
        {
            return data;
        }

        virtual typename Tensor3::DataType& GetGradient3D()
        {
            return gradient;
        }

    protected:
        std::shared_ptr<FlattenLayer> flattenLayer;
    };

    std::shared_ptr<FlattenLayer> Tensor3DLayer::Flatten()
    {
        auto flatten = std::shared_ptr<FlattenLayer>(new FlattenLayer());
        this->flattenLayer = flatten;
        flatten->SetSourceLayer(this);
        flatten->Initialize();
        return flatten;
    }
}
