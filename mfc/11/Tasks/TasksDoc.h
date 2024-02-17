
// TasksDoc.h: интерфейс класса CTasksDoc
//


#pragma once


class CTasksDoc : public CDocument {
protected:  // создать только из сериализации
    CTasksDoc() noexcept;
    DECLARE_DYNCREATE(CTasksDoc)

    // Атрибуты
public:
    // Операции
public:
    // Переопределение
public:
    virtual BOOL OnNewDocument();
    virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
    virtual void InitializeSearchContent();
    virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif  // SHARED_HANDLERS

    // Реализация
public:
    virtual ~CTasksDoc();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:
    // Созданные функции схемы сообщений
protected:
    DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
    // Вспомогательная функция, задающая содержимое поиска для обработчика поиска
    void SetSearchContent(const CString& value);
#endif  // SHARED_HANDLERS
};
