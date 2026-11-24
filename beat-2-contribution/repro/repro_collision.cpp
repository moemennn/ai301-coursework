// Stores two DIFFERENT payloads under two object IDs, then reads them back through ObjectManager's public API.
#include <cstdio>
#include <memory>
#include <string>

#include "scaler/object_storage/object_manager.h"
#include "scaler/ymq/buffered_bytes.h"

using scaler::object_storage::ObjectID;
using scaler::object_storage::ObjectManager;

static std::string show(const std::shared_ptr<const scaler::object_storage::ObjectPayload>& payload)
{
    return payload ? "\"" + payload->asString().value_or("<non-string>") + "\"" : "<null>";
}

int main()
{
    ObjectManager manager;
    const ObjectID idA {1, 0, 0, 0};
    const ObjectID idB {2, 0, 0, 0};

    manager.setObject(idA, std::make_unique<scaler::ymq::BufferedBytes>(std::string("payload-A")));
    auto returnedForB = manager.setObject(idB, std::make_unique<scaler::ymq::BufferedBytes>(std::string("payload-B")));

    std::printf("setObject(B) returned        %s\n", show(returnedForB).c_str());
    std::printf("getObject(A)                 %s\n", show(manager.getObject(idA)).c_str());
    std::printf("getObject(B)                 %s   (expected \"payload-B\")\n", show(manager.getObject(idB)).c_str());
    std::printf("size()=%zu sizeUnique()=%zu totalObjectsSize()=%zu   (expected 2, 2, 18)\n",
                manager.size(), manager.sizeUnique(), manager.totalObjectsSize());

    manager.deleteObject(idA);
    std::printf("after deleteObject(A): getObject(B) %s   (expected \"payload-B\")\n",
                show(manager.getObject(idB)).c_str());

    const bool bIsCorrect = manager.getObject(idB) && manager.getObject(idB)->asString() == "payload-B";
    std::printf("RESULT: %s\n", bIsCorrect ? "B round-trips correctly" : "B's bytes were replaced by A's");
    return bIsCorrect ? 0 : 1;
}
