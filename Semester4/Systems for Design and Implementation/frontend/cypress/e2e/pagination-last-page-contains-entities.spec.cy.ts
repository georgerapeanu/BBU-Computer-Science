describe('Test that the last page of pagination contains at least one entity', () => {
  it('passes', () => {
    cy.visit('/users')
    cy.wait(3000);
    cy.get("app-pagination div .lastPageButton").click();
    cy.wait(3000);
    cy.get("table tbody tr").should('have.length.gt', 0);
  })
})