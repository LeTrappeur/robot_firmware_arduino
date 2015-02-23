namespace Rbt
{
    class DistanceSensorDriver
    {
    public:
        DistanceSensorDriver(unsigned int distance) : maxDistance(distance) {}
        virtual unsigned int getDistance() = 0;

    protected:
        unsigned int maxDistance;
    };
};
