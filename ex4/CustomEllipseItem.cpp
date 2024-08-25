// @author shay.gali@msmail.ariel.ac.il
#include "CustomEllipseItem.hpp"

CustomEllipseItem::CustomEllipseItem(qreal x, qreal y, qreal w, qreal h, const QString& data, QGraphicsItem* parent)
    : QGraphicsEllipseItem(x, y, w, h, parent), nodeData(data) {
    setAcceptHoverEvents(true);
}

void CustomEllipseItem::hoverEnterEvent(QGraphicsSceneHoverEvent* event) {
    if (!textItem) {
        textItem = new QGraphicsTextItem(nodeData, this);
        // Adjust text position as needed
        QPointF textPos = mapToScene(rect().topRight());  // Example position
        qreal offsetX = 10;                               // Offset to not overlap the circle
        qreal offsetY = -textItem->boundingRect().height() / 2;
        textItem->setPos(textPos.x() + offsetX, textPos.y() + offsetY);
        textItem->setDefaultTextColor(Qt::black);

        // Create a square (rectangle) around the text
        qreal padding = 5;                             // Padding around the text
        QRectF textBounds = textItem->boundingRect();  // Get the bounding rectangle of the text
        // Create a rectangle around the text
        QRectF rectBounds(textBounds.x() - padding, textBounds.y() - padding, textBounds.width() + 2 * padding, textBounds.height() + 2 * padding);
        rectItem = new QGraphicsRectItem(rectBounds, textItem);  // Make the rectangle a child of the text item
        rectItem->setPen(QPen(Qt::black));                       // Set the color of the square

        textItem->setVisible(true);
        rectItem->setVisible(true);
    }
    QGraphicsEllipseItem::hoverEnterEvent(event);
}

void CustomEllipseItem::hoverLeaveEvent(QGraphicsSceneHoverEvent* event) {
    if (textItem) {
        delete textItem;  // This also deletes the rectangle since it's a child of the text item
        textItem = nullptr;
        rectItem = nullptr;  // The rectangle is deleted with the text item
    }
    QGraphicsEllipseItem::hoverLeaveEvent(event);
}
