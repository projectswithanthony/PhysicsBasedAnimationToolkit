#ifndef PBAT_GPU_XPBD_XPBD_H
#define PBAT_GPU_XPBD_XPBD_H

#define EIGEN_NO_CUDA
#include "pbat/Aliases.h"
#undef EIGEN_NO_CUDA

#include "pbat/gpu/Aliases.h"

#include <array>
#include <cstddef>
#include <vector>

namespace pbat {
namespace gpu {
namespace xpbd {

class XpbdImpl;

class Xpbd
{
  public:
    enum EConstraint { StableNeoHookean = 0, Collision };

    // Constructors
    /**
     * @brief
     * @param V
     * @param T
     */
    Xpbd(
        Eigen::Ref<GpuMatrixX const> const& V,
        Eigen::Ref<GpuIndexMatrixX const> const& F,
        Eigen::Ref<GpuIndexMatrixX const> const& T);
    Xpbd(Xpbd const&)            = delete;
    Xpbd& operator=(Xpbd const&) = delete;
    Xpbd(Xpbd&&) noexcept;
    Xpbd& operator=(Xpbd&&) noexcept;
    /**
     * @brief
     */
    void PrepareConstraints();
    /**
     * @brief
     * @param dt
     * @param iterations
     * @params substeps
     */
    void Step(GpuScalar dt, GpuIndex iterations, GpuIndex substeps);
    /**
     * @brief
     * @return
     */
    GpuMatrixX Positions() const;
    /**
     * @brief
     * @return
     */
    std::size_t NumberOfParticles() const;
    /**
     * @brief
     * @return
     */
    std::size_t NumberOfConstraints() const;
    /**
     * @brief
     * @param X
     */
    void SetPositions(Eigen::Ref<GpuMatrixX const> const& X);
    /**
     * @brief
     * @param v
     */
    void SetVelocities(Eigen::Ref<GpuMatrixX const> const& v);
    /**
     * @brief
     * @param f
     */
    void SetExternalForces(Eigen::Ref<GpuMatrixX const> const& f);
    /**
     * @brief
     * @param m
     */
    void SetMass(Eigen::Ref<GpuMatrixX const> const& m);
    /**
     * @brief
     * @param l
     */
    void SetLameCoefficients(Eigen::Ref<GpuMatrixX const> const& l);
    /**
     * @brief
     * @param partitions
     */
    void SetConstraintPartitions(std::vector<std::vector<GpuIndex>> const& partitions);
    /**
     * @brief
     * @return
     */
    GpuMatrixX GetVelocity() const;
    /**
     * @brief
     * @return
     */
    GpuMatrixX GetExternalForce() const;
    /**
     * @brief
     * @return
     */
    GpuVectorX GetMass() const;
    /**
     * @brief
     * @return
     */
    GpuMatrixX GetLameCoefficients() const;
    /**
     * @brief
     * @return
     */
    GpuMatrixX GetShapeMatrixInverse() const;
    /**
     * @brief
     * @return
     */
    GpuMatrixX GetRestStableGamma() const;
    /**
     * @brief
     * @param eConstraint
     * @return
     */
    GpuMatrixX GetLagrangeMultiplier(EConstraint eConstraint) const;
    /**
     * @brief
     * @param eConstraint
     * @return
     */
    GpuMatrixX GetCompliance(EConstraint eConstraint) const;
    /**
     * @brief
     * @return
     */
    std::vector<std::vector<GpuIndex>> GetPartitions() const;
    /**
     * @brief
     */
    ~Xpbd();

  private:
    XpbdImpl* mImpl;
};

} // namespace xpbd
} // namespace gpu
} // namespace pbat

#endif // PBAT_GPU_XPBD_XPBD_H